#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hfi1_devdata {int flags; int /*<<< orphan*/  node; int /*<<< orphan*/  pport; } ;
struct hfi1_ctxtdata {int flags; int seq_cnt; int is_vnic; int /*<<< orphan*/  ctxt; } ;
struct TYPE_2__ {int /*<<< orphan*/  sps_ctxts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 int EIO ; 
 int ENOMEM ; 
 int HFI1_CAP_KGET (int /*<<< orphan*/ ) ; 
 int HFI1_FROZEN ; 
 int /*<<< orphan*/  MULTI_PKT_EGR ; 
 int /*<<< orphan*/  NODROP_EGR_FULL ; 
 int /*<<< orphan*/  NODROP_RHQ_FULL ; 
 int /*<<< orphan*/  dd_dev_dbg (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int hfi1_create_ctxtdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfi1_ctxtdata**) ; 
 TYPE_1__ hfi1_stats ; 
 int /*<<< orphan*/  msix_request_rcd_irq (struct hfi1_ctxtdata*) ; 

__attribute__((used)) static int allocate_vnic_ctxt(struct hfi1_devdata *dd,
			      struct hfi1_ctxtdata **vnic_ctxt)
{
	struct hfi1_ctxtdata *uctxt;
	int ret;

	if (dd->flags & HFI1_FROZEN)
		return -EIO;

	ret = hfi1_create_ctxtdata(dd->pport, dd->node, &uctxt);
	if (ret < 0) {
		dd_dev_err(dd, "Unable to create ctxtdata, failing open\n");
		return -ENOMEM;
	}

	uctxt->flags = HFI1_CAP_KGET(MULTI_PKT_EGR) |
			HFI1_CAP_KGET(NODROP_RHQ_FULL) |
			HFI1_CAP_KGET(NODROP_EGR_FULL) |
			HFI1_CAP_KGET(DMA_RTAIL);
	uctxt->seq_cnt = 1;
	uctxt->is_vnic = true;

	msix_request_rcd_irq(uctxt);

	hfi1_stats.sps_ctxts++;
	dd_dev_dbg(dd, "created vnic context %d\n", uctxt->ctxt);
	*vnic_ctxt = uctxt;

	return 0;
}