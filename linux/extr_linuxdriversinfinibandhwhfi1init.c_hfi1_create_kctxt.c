#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hfi1_pportdata {int dummy; } ;
struct hfi1_devdata {int /*<<< orphan*/  node; } ;
struct hfi1_ctxtdata {int flags; scalar_t__ ctxt; int seq_cnt; int /*<<< orphan*/  sc; int /*<<< orphan*/  rcvhdrqentsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_RTAIL ; 
 int ENOMEM ; 
 int HFI1_CAP_DMA_RTAIL ; 
 int HFI1_CAP_KGET (int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_CTRL_CTXT ; 
 int /*<<< orphan*/  MULTI_PKT_EGR ; 
 int /*<<< orphan*/  NODROP_EGR_FULL ; 
 int /*<<< orphan*/  NODROP_RHQ_FULL ; 
 int /*<<< orphan*/  SC_ACK ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int hfi1_create_ctxtdata (struct hfi1_pportdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata**) ; 
 int /*<<< orphan*/  hfi1_init_ctxt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_alloc (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfi1_create_kctxt(struct hfi1_devdata *dd,
			     struct hfi1_pportdata *ppd)
{
	struct hfi1_ctxtdata *rcd;
	int ret;

	/* Control context has to be always 0 */
	BUILD_BUG_ON(HFI1_CTRL_CTXT != 0);

	ret = hfi1_create_ctxtdata(ppd, dd->node, &rcd);
	if (ret < 0) {
		dd_dev_err(dd, "Kernel receive context allocation failed\n");
		return ret;
	}

	/*
	 * Set up the kernel context flags here and now because they use
	 * default values for all receive side memories.  User contexts will
	 * be handled as they are created.
	 */
	rcd->flags = HFI1_CAP_KGET(MULTI_PKT_EGR) |
		HFI1_CAP_KGET(NODROP_RHQ_FULL) |
		HFI1_CAP_KGET(NODROP_EGR_FULL) |
		HFI1_CAP_KGET(DMA_RTAIL);

	/* Control context must use DMA_RTAIL */
	if (rcd->ctxt == HFI1_CTRL_CTXT)
		rcd->flags |= HFI1_CAP_DMA_RTAIL;
	rcd->seq_cnt = 1;

	rcd->sc = sc_alloc(dd, SC_ACK, rcd->rcvhdrqentsize, dd->node);
	if (!rcd->sc) {
		dd_dev_err(dd, "Kernel send context allocation failed\n");
		return -ENOMEM;
	}
	hfi1_init_ctxt(rcd->sc);

	return 0;
}