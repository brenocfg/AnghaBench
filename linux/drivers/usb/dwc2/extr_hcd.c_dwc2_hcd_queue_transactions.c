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
typedef  int /*<<< orphan*/  u32 ;
struct dwc2_hsotg {int /*<<< orphan*/  non_periodic_sched_active; int /*<<< orphan*/  dev; } ;
typedef  enum dwc2_transaction_type { ____Placeholder_dwc2_transaction_type } dwc2_transaction_type ;

/* Variables and functions */
 int DWC2_TRANSACTION_ALL ; 
 int DWC2_TRANSACTION_NON_PERIODIC ; 
 int DWC2_TRANSACTION_PERIODIC ; 
 int /*<<< orphan*/  GINTMSK ; 
 int /*<<< orphan*/  GINTSTS_NPTXFEMP ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_process_non_periodic_channels (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_process_periodic_channels (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void dwc2_hcd_queue_transactions(struct dwc2_hsotg *hsotg,
				 enum dwc2_transaction_type tr_type)
{
#ifdef DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "Queue Transactions\n");
#endif
	/* Process host channels associated with periodic transfers */
	if (tr_type == DWC2_TRANSACTION_PERIODIC ||
	    tr_type == DWC2_TRANSACTION_ALL)
		dwc2_process_periodic_channels(hsotg);

	/* Process host channels associated with non-periodic transfers */
	if (tr_type == DWC2_TRANSACTION_NON_PERIODIC ||
	    tr_type == DWC2_TRANSACTION_ALL) {
		if (!list_empty(&hsotg->non_periodic_sched_active)) {
			dwc2_process_non_periodic_channels(hsotg);
		} else {
			/*
			 * Ensure NP Tx FIFO empty interrupt is disabled when
			 * there are no non-periodic transfers to process
			 */
			u32 gintmsk = dwc2_readl(hsotg, GINTMSK);

			gintmsk &= ~GINTSTS_NPTXFEMP;
			dwc2_writel(hsotg, gintmsk, GINTMSK);
		}
	}
}