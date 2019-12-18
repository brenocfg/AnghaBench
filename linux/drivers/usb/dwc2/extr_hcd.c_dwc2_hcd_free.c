#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ snpsid; } ;
struct TYPE_3__ {scalar_t__ host_dma; } ;
struct dwc2_hsotg {int /*<<< orphan*/  wkp_timer; int /*<<< orphan*/  phy_reset_work; scalar_t__ wq_otg; int /*<<< orphan*/  wf_otg; TYPE_2__ hw_params; struct dwc2_host_chan* status_buf; int /*<<< orphan*/  status_buf_dma; int /*<<< orphan*/  dev; TYPE_1__ params; struct dwc2_host_chan** hc_ptr_array; int /*<<< orphan*/  periodic_sched_queued; int /*<<< orphan*/  periodic_sched_assigned; int /*<<< orphan*/  periodic_sched_ready; int /*<<< orphan*/  periodic_sched_inactive; int /*<<< orphan*/  non_periodic_sched_active; int /*<<< orphan*/  non_periodic_sched_waiting; int /*<<< orphan*/  non_periodic_sched_inactive; } ;
struct dwc2_host_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCTL ; 
 int /*<<< orphan*/  DCTL_SFTDISCON ; 
 scalar_t__ DWC2_CORE_REV_3_00a ; 
 int /*<<< orphan*/  DWC2_HCD_STATUS_BUF_SIZE ; 
 int /*<<< orphan*/  GAHBCFG ; 
 int /*<<< orphan*/  GAHBCFG_GLBL_INTR_EN ; 
 int /*<<< orphan*/  GINTMSK ; 
 int MAX_EPS_CHANNELS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dwc2_host_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_qh_list_free (struct dwc2_hsotg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dwc2_host_chan*) ; 

__attribute__((used)) static void dwc2_hcd_free(struct dwc2_hsotg *hsotg)
{
	u32 ahbcfg;
	u32 dctl;
	int i;

	dev_dbg(hsotg->dev, "DWC OTG HCD FREE\n");

	/* Free memory for QH/QTD lists */
	dwc2_qh_list_free(hsotg, &hsotg->non_periodic_sched_inactive);
	dwc2_qh_list_free(hsotg, &hsotg->non_periodic_sched_waiting);
	dwc2_qh_list_free(hsotg, &hsotg->non_periodic_sched_active);
	dwc2_qh_list_free(hsotg, &hsotg->periodic_sched_inactive);
	dwc2_qh_list_free(hsotg, &hsotg->periodic_sched_ready);
	dwc2_qh_list_free(hsotg, &hsotg->periodic_sched_assigned);
	dwc2_qh_list_free(hsotg, &hsotg->periodic_sched_queued);

	/* Free memory for the host channels */
	for (i = 0; i < MAX_EPS_CHANNELS; i++) {
		struct dwc2_host_chan *chan = hsotg->hc_ptr_array[i];

		if (chan) {
			dev_dbg(hsotg->dev, "HCD Free channel #%i, chan=%p\n",
				i, chan);
			hsotg->hc_ptr_array[i] = NULL;
			kfree(chan);
		}
	}

	if (hsotg->params.host_dma) {
		if (hsotg->status_buf) {
			dma_free_coherent(hsotg->dev, DWC2_HCD_STATUS_BUF_SIZE,
					  hsotg->status_buf,
					  hsotg->status_buf_dma);
			hsotg->status_buf = NULL;
		}
	} else {
		kfree(hsotg->status_buf);
		hsotg->status_buf = NULL;
	}

	ahbcfg = dwc2_readl(hsotg, GAHBCFG);

	/* Disable all interrupts */
	ahbcfg &= ~GAHBCFG_GLBL_INTR_EN;
	dwc2_writel(hsotg, ahbcfg, GAHBCFG);
	dwc2_writel(hsotg, 0, GINTMSK);

	if (hsotg->hw_params.snpsid >= DWC2_CORE_REV_3_00a) {
		dctl = dwc2_readl(hsotg, DCTL);
		dctl |= DCTL_SFTDISCON;
		dwc2_writel(hsotg, dctl, DCTL);
	}

	if (hsotg->wq_otg) {
		if (!cancel_work_sync(&hsotg->wf_otg))
			flush_workqueue(hsotg->wq_otg);
		destroy_workqueue(hsotg->wq_otg);
	}

	cancel_work_sync(&hsotg->phy_reset_work);

	del_timer(&hsotg->wkp_timer);
}