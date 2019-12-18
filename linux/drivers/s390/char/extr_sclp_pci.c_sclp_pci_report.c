#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct zpci_report_error_header {scalar_t__ length; int /*<<< orphan*/  data; int /*<<< orphan*/  action; } ;
struct sclp_req {scalar_t__ status; struct err_notify_sccb* sccb; int /*<<< orphan*/  command; int /*<<< orphan*/  callback; int /*<<< orphan*/ * callback_data; } ;
struct TYPE_9__ {int response_code; scalar_t__ length; } ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; void* fid; void* fh; int /*<<< orphan*/  atype; int /*<<< orphan*/  action; TYPE_1__ header; } ;
struct err_notify_sccb {TYPE_3__ header; TYPE_2__ evbuf; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_10__ {int sclp_receive_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVTYP_ERRNOTIFY ; 
 int EVTYP_ERRNOTIFY_MASK ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_ATYPE_PCI ; 
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 scalar_t__ SCLP_REQ_DONE ; 
 scalar_t__ SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sclp_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int sclp_add_request (struct sclp_req*) ; 
 int /*<<< orphan*/  sclp_pci_callback ; 
 int sclp_pci_check_report (struct zpci_report_error_header*) ; 
 TYPE_4__ sclp_pci_event ; 
 int /*<<< orphan*/  sclp_pci_mutex ; 
 int sclp_register (TYPE_4__*) ; 
 int /*<<< orphan*/  sclp_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int sclp_pci_report(struct zpci_report_error_header *report, u32 fh, u32 fid)
{
	DECLARE_COMPLETION_ONSTACK(completion);
	struct err_notify_sccb *sccb;
	struct sclp_req req;
	int ret;

	ret = sclp_pci_check_report(report);
	if (ret)
		return ret;

	mutex_lock(&sclp_pci_mutex);
	ret = sclp_register(&sclp_pci_event);
	if (ret)
		goto out_unlock;

	if (!(sclp_pci_event.sclp_receive_mask & EVTYP_ERRNOTIFY_MASK)) {
		ret = -EOPNOTSUPP;
		goto out_unregister;
	}

	sccb = (void *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!sccb) {
		ret = -ENOMEM;
		goto out_unregister;
	}

	memset(&req, 0, sizeof(req));
	req.callback_data = &completion;
	req.callback = sclp_pci_callback;
	req.command = SCLP_CMDW_WRITE_EVENT_DATA;
	req.status = SCLP_REQ_FILLED;
	req.sccb = sccb;

	sccb->evbuf.header.length = sizeof(sccb->evbuf) + report->length;
	sccb->evbuf.header.type = EVTYP_ERRNOTIFY;
	sccb->header.length = sizeof(sccb->header) + sccb->evbuf.header.length;

	sccb->evbuf.action = report->action;
	sccb->evbuf.atype = SCLP_ATYPE_PCI;
	sccb->evbuf.fh = fh;
	sccb->evbuf.fid = fid;

	memcpy(sccb->evbuf.data, report->data, report->length);

	ret = sclp_add_request(&req);
	if (ret)
		goto out_free_req;

	wait_for_completion(&completion);
	if (req.status != SCLP_REQ_DONE) {
		pr_warn("request failed (status=0x%02x)\n",
			req.status);
		ret = -EIO;
		goto out_free_req;
	}

	if (sccb->header.response_code != 0x0020) {
		pr_warn("request failed with response code 0x%x\n",
			sccb->header.response_code);
		ret = -EIO;
	}

out_free_req:
	free_page((unsigned long) sccb);
out_unregister:
	sclp_unregister(&sclp_pci_event);
out_unlock:
	mutex_unlock(&sclp_pci_mutex);
	return ret;
}