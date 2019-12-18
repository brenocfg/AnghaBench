#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; int response_code; } ;
struct TYPE_5__ {int length; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int event_id; int dbs; int /*<<< orphan*/  data_id; int /*<<< orphan*/  event_qual; TYPE_1__ hdr; } ;
struct sdias_sccb {TYPE_3__ hdr; int /*<<< orphan*/  callback; int /*<<< orphan*/  status; int /*<<< orphan*/  command; struct sdias_sccb* sccb; TYPE_2__ evbuf; } ;
struct sdias_evbuf {int dummy; } ;
struct sclp_req {TYPE_3__ hdr; int /*<<< orphan*/  callback; int /*<<< orphan*/  status; int /*<<< orphan*/  command; struct sclp_req* sccb; TYPE_2__ evbuf; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_8__ {int event_status; int blk_cnt; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EVTYP_SDIAS ; 
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 int /*<<< orphan*/  SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  SDIAS_DI_FCP_DUMP ; 
 int /*<<< orphan*/  SDIAS_EQ_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  memset (struct sdias_sccb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct sdias_sccb* sclp_sdias_sccb ; 
 int /*<<< orphan*/  sdias_callback ; 
 TYPE_4__ sdias_evbuf ; 
 int /*<<< orphan*/  sdias_mutex ; 
 int sdias_sclp_send (struct sdias_sccb*) ; 

int sclp_sdias_blk_count(void)
{
	struct sdias_sccb *sccb = sclp_sdias_sccb;
	struct sclp_req request;
	int rc;

	mutex_lock(&sdias_mutex);

	memset(sccb, 0, sizeof(*sccb));
	memset(&request, 0, sizeof(request));

	sccb->hdr.length = sizeof(*sccb);
	sccb->evbuf.hdr.length = sizeof(struct sdias_evbuf);
	sccb->evbuf.hdr.type = EVTYP_SDIAS;
	sccb->evbuf.event_qual = SDIAS_EQ_SIZE;
	sccb->evbuf.data_id = SDIAS_DI_FCP_DUMP;
	sccb->evbuf.event_id = 4712;
	sccb->evbuf.dbs = 1;

	request.sccb = sccb;
	request.command = SCLP_CMDW_WRITE_EVENT_DATA;
	request.status = SCLP_REQ_FILLED;
	request.callback = sdias_callback;

	rc = sdias_sclp_send(&request);
	if (rc) {
		pr_err("sclp_send failed for get_nr_blocks\n");
		goto out;
	}
	if (sccb->hdr.response_code != 0x0020) {
		TRACE("send failed: %x\n", sccb->hdr.response_code);
		rc = -EIO;
		goto out;
	}

	switch (sdias_evbuf.event_status) {
		case 0:
			rc = sdias_evbuf.blk_cnt;
			break;
		default:
			pr_err("SCLP error: %x\n", sdias_evbuf.event_status);
			rc = -EIO;
			goto out;
	}
	TRACE("%i blocks\n", rc);
out:
	mutex_unlock(&sdias_mutex);
	return rc;
}