#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sclp_req {scalar_t__ status; struct completion* callback_data; int /*<<< orphan*/  callback; struct sclp_diag_sccb* sccb; int /*<<< orphan*/  command; } ;
struct TYPE_10__ {int response_code; void* length; } ;
struct TYPE_8__ {int flags; void* length; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  fident; int /*<<< orphan*/  bufaddr; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  cmd; scalar_t__ fsize; int /*<<< orphan*/  ldflg; int /*<<< orphan*/  asce; scalar_t__ pgsize; scalar_t__ srcflg; int /*<<< orphan*/  pcx; } ;
struct TYPE_7__ {TYPE_1__ ftp; } ;
struct TYPE_9__ {TYPE_3__ hdr; TYPE_2__ mdd; int /*<<< orphan*/  route; } ;
struct sclp_diag_sccb {TYPE_5__ hdr; TYPE_4__ evbuf; } ;
struct sccb_header {int dummy; } ;
struct hmcdrv_ftp_cmdspec {int /*<<< orphan*/  fname; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; int /*<<< orphan*/  ofs; int /*<<< orphan*/  id; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVTYP_DIAG_TEST ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 size_t HMCDRV_FTP_FIDENT_MAX ; 
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 void* SCLP_DIAG_FTP_EVBUF_LEN ; 
 int /*<<< orphan*/  SCLP_DIAG_FTP_LDFAIL ; 
 int /*<<< orphan*/  SCLP_DIAG_FTP_ROUTE ; 
 int /*<<< orphan*/  SCLP_DIAG_FTP_XPCX ; 
 scalar_t__ SCLP_REQ_DONE ; 
 scalar_t__ SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  _ASCE_REAL_SPACE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  kfree (struct sclp_req*) ; 
 struct sclp_req* kzalloc (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int sclp_add_request (struct sclp_req*) ; 
 int /*<<< orphan*/  sclp_ftp_txcb ; 
 size_t strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static int sclp_ftp_et7(const struct hmcdrv_ftp_cmdspec *ftp)
{
	struct completion completion;
	struct sclp_diag_sccb *sccb;
	struct sclp_req *req;
	size_t len;
	int rc;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	sccb = (void *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!req || !sccb) {
		rc = -ENOMEM;
		goto out_free;
	}

	sccb->hdr.length = SCLP_DIAG_FTP_EVBUF_LEN +
		sizeof(struct sccb_header);
	sccb->evbuf.hdr.type = EVTYP_DIAG_TEST;
	sccb->evbuf.hdr.length = SCLP_DIAG_FTP_EVBUF_LEN;
	sccb->evbuf.hdr.flags = 0; /* clear processed-buffer */
	sccb->evbuf.route = SCLP_DIAG_FTP_ROUTE;
	sccb->evbuf.mdd.ftp.pcx = SCLP_DIAG_FTP_XPCX;
	sccb->evbuf.mdd.ftp.srcflg = 0;
	sccb->evbuf.mdd.ftp.pgsize = 0;
	sccb->evbuf.mdd.ftp.asce = _ASCE_REAL_SPACE;
	sccb->evbuf.mdd.ftp.ldflg = SCLP_DIAG_FTP_LDFAIL;
	sccb->evbuf.mdd.ftp.fsize = 0;
	sccb->evbuf.mdd.ftp.cmd = ftp->id;
	sccb->evbuf.mdd.ftp.offset = ftp->ofs;
	sccb->evbuf.mdd.ftp.length = ftp->len;
	sccb->evbuf.mdd.ftp.bufaddr = virt_to_phys(ftp->buf);

	len = strlcpy(sccb->evbuf.mdd.ftp.fident, ftp->fname,
		      HMCDRV_FTP_FIDENT_MAX);
	if (len >= HMCDRV_FTP_FIDENT_MAX) {
		rc = -EINVAL;
		goto out_free;
	}

	req->command = SCLP_CMDW_WRITE_EVENT_DATA;
	req->sccb = sccb;
	req->status = SCLP_REQ_FILLED;
	req->callback = sclp_ftp_txcb;
	req->callback_data = &completion;

	init_completion(&completion);

	rc = sclp_add_request(req);
	if (rc)
		goto out_free;

	/* Wait for end of ftp sclp command. */
	wait_for_completion(&completion);

#ifdef DEBUG
	pr_debug("status of SCLP (ET7) request is 0x%04x (0x%02x)\n",
		 sccb->hdr.response_code, sccb->evbuf.hdr.flags);
#endif

	/*
	 * Check if sclp accepted the request. The data transfer runs
	 * asynchronously and the completion is indicated with an
	 * sclp ET7 event.
	 */
	if (req->status != SCLP_REQ_DONE ||
	    (sccb->evbuf.hdr.flags & 0x80) == 0 || /* processed-buffer */
	    (sccb->hdr.response_code & 0xffU) != 0x20U) {
		rc = -EIO;
	}

out_free:
	free_page((unsigned long) sccb);
	kfree(req);
	return rc;
}