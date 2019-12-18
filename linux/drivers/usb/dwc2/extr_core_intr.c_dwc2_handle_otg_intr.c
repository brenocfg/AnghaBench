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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ snpsid; } ;
struct TYPE_3__ {scalar_t__ phy_type; scalar_t__ i2c_enable; } ;
struct dwc2_hsotg {void* op_state; int srp_success; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_2__ hw_params; TYPE_1__ params; int /*<<< orphan*/  lx_state; } ;

/* Variables and functions */
 scalar_t__ DWC2_CORE_REV_3_00a ; 
 int /*<<< orphan*/  DWC2_L0 ; 
 scalar_t__ DWC2_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  GINTMSK ; 
 int GINTSTS_SOF ; 
 int /*<<< orphan*/  GOTGCTL ; 
 int GOTGCTL_DEVHNPEN ; 
 int GOTGCTL_HNPREQ ; 
 int GOTGCTL_HSTNEGSCS ; 
 int GOTGCTL_SESREQ ; 
 int GOTGCTL_SESREQSCS ; 
 int /*<<< orphan*/  GOTGINT ; 
 int GOTGINT_A_DEV_TOUT_CHG ; 
 int GOTGINT_DBNCE_DONE ; 
 int GOTGINT_HST_NEG_DET ; 
 int GOTGINT_HST_NEG_SUC_STS_CHNG ; 
 int GOTGINT_SES_END_DET ; 
 int GOTGINT_SES_REQ_SUC_STS_CHNG ; 
 void* OTG_STATE_A_HOST ; 
 void* OTG_STATE_A_PERIPHERAL ; 
 void* OTG_STATE_B_HOST ; 
 void* OTG_STATE_B_PERIPHERAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_hcd_disconnect (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_hcd_start (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_disconnect (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_is_device_mode (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_is_host_mode (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_op_state_str (struct dwc2_hsotg*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dwc2_handle_otg_intr(struct dwc2_hsotg *hsotg)
{
	u32 gotgint;
	u32 gotgctl;
	u32 gintmsk;

	gotgint = dwc2_readl(hsotg, GOTGINT);
	gotgctl = dwc2_readl(hsotg, GOTGCTL);
	dev_dbg(hsotg->dev, "++OTG Interrupt gotgint=%0x [%s]\n", gotgint,
		dwc2_op_state_str(hsotg));

	if (gotgint & GOTGINT_SES_END_DET) {
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: Session End Detected++ (%s)\n",
			dwc2_op_state_str(hsotg));
		gotgctl = dwc2_readl(hsotg, GOTGCTL);

		if (dwc2_is_device_mode(hsotg))
			dwc2_hsotg_disconnect(hsotg);

		if (hsotg->op_state == OTG_STATE_B_HOST) {
			hsotg->op_state = OTG_STATE_B_PERIPHERAL;
		} else {
			/*
			 * If not B_HOST and Device HNP still set, HNP did
			 * not succeed!
			 */
			if (gotgctl & GOTGCTL_DEVHNPEN) {
				dev_dbg(hsotg->dev, "Session End Detected\n");
				dev_err(hsotg->dev,
					"Device Not Connected/Responding!\n");
			}

			/*
			 * If Session End Detected the B-Cable has been
			 * disconnected
			 */
			/* Reset to a clean state */
			hsotg->lx_state = DWC2_L0;
		}

		gotgctl = dwc2_readl(hsotg, GOTGCTL);
		gotgctl &= ~GOTGCTL_DEVHNPEN;
		dwc2_writel(hsotg, gotgctl, GOTGCTL);
	}

	if (gotgint & GOTGINT_SES_REQ_SUC_STS_CHNG) {
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: Session Request Success Status Change++\n");
		gotgctl = dwc2_readl(hsotg, GOTGCTL);
		if (gotgctl & GOTGCTL_SESREQSCS) {
			if (hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS &&
			    hsotg->params.i2c_enable) {
				hsotg->srp_success = 1;
			} else {
				/* Clear Session Request */
				gotgctl = dwc2_readl(hsotg, GOTGCTL);
				gotgctl &= ~GOTGCTL_SESREQ;
				dwc2_writel(hsotg, gotgctl, GOTGCTL);
			}
		}
	}

	if (gotgint & GOTGINT_HST_NEG_SUC_STS_CHNG) {
		/*
		 * Print statements during the HNP interrupt handling
		 * can cause it to fail
		 */
		gotgctl = dwc2_readl(hsotg, GOTGCTL);
		/*
		 * WA for 3.00a- HW is not setting cur_mode, even sometimes
		 * this does not help
		 */
		if (hsotg->hw_params.snpsid >= DWC2_CORE_REV_3_00a)
			udelay(100);
		if (gotgctl & GOTGCTL_HSTNEGSCS) {
			if (dwc2_is_host_mode(hsotg)) {
				hsotg->op_state = OTG_STATE_B_HOST;
				/*
				 * Need to disable SOF interrupt immediately.
				 * When switching from device to host, the PCD
				 * interrupt handler won't handle the interrupt
				 * if host mode is already set. The HCD
				 * interrupt handler won't get called if the
				 * HCD state is HALT. This means that the
				 * interrupt does not get handled and Linux
				 * complains loudly.
				 */
				gintmsk = dwc2_readl(hsotg, GINTMSK);
				gintmsk &= ~GINTSTS_SOF;
				dwc2_writel(hsotg, gintmsk, GINTMSK);

				/*
				 * Call callback function with spin lock
				 * released
				 */
				spin_unlock(&hsotg->lock);

				/* Initialize the Core for Host mode */
				dwc2_hcd_start(hsotg);
				spin_lock(&hsotg->lock);
				hsotg->op_state = OTG_STATE_B_HOST;
			}
		} else {
			gotgctl = dwc2_readl(hsotg, GOTGCTL);
			gotgctl &= ~(GOTGCTL_HNPREQ | GOTGCTL_DEVHNPEN);
			dwc2_writel(hsotg, gotgctl, GOTGCTL);
			dev_dbg(hsotg->dev, "HNP Failed\n");
			dev_err(hsotg->dev,
				"Device Not Connected/Responding\n");
		}
	}

	if (gotgint & GOTGINT_HST_NEG_DET) {
		/*
		 * The disconnect interrupt is set at the same time as
		 * Host Negotiation Detected. During the mode switch all
		 * interrupts are cleared so the disconnect interrupt
		 * handler will not get executed.
		 */
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: Host Negotiation Detected++ (%s)\n",
			(dwc2_is_host_mode(hsotg) ? "Host" : "Device"));
		if (dwc2_is_device_mode(hsotg)) {
			dev_dbg(hsotg->dev, "a_suspend->a_peripheral (%d)\n",
				hsotg->op_state);
			spin_unlock(&hsotg->lock);
			dwc2_hcd_disconnect(hsotg, false);
			spin_lock(&hsotg->lock);
			hsotg->op_state = OTG_STATE_A_PERIPHERAL;
		} else {
			/* Need to disable SOF interrupt immediately */
			gintmsk = dwc2_readl(hsotg, GINTMSK);
			gintmsk &= ~GINTSTS_SOF;
			dwc2_writel(hsotg, gintmsk, GINTMSK);
			spin_unlock(&hsotg->lock);
			dwc2_hcd_start(hsotg);
			spin_lock(&hsotg->lock);
			hsotg->op_state = OTG_STATE_A_HOST;
		}
	}

	if (gotgint & GOTGINT_A_DEV_TOUT_CHG)
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: A-Device Timeout Change++\n");
	if (gotgint & GOTGINT_DBNCE_DONE)
		dev_dbg(hsotg->dev, " ++OTG Interrupt: Debounce Done++\n");

	/* Clear GOTGINT */
	dwc2_writel(hsotg, gotgint, GOTGINT);
}