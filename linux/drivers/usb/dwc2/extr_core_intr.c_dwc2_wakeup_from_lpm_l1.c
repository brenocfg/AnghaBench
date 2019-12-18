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
typedef  int u32 ;
struct dwc2_hsotg {scalar_t__ lx_state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DWC2_L0 ; 
 scalar_t__ DWC2_L1 ; 
 int /*<<< orphan*/  GLPMCFG ; 
 int GLPMCFG_COREL1RES_MASK ; 
 int GLPMCFG_ENBLSLPM ; 
 int GLPMCFG_HIRD_THRES_EN ; 
 int GLPMCFG_L1RESUMEOK ; 
 int GLPMCFG_SLPSTS ; 
 int /*<<< orphan*/  call_gadget (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_gadget_init_lpm (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_is_device_mode (struct dwc2_hsotg*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dwc2_wakeup_from_lpm_l1(struct dwc2_hsotg *hsotg)
{
	u32 glpmcfg;
	u32 i = 0;

	if (hsotg->lx_state != DWC2_L1) {
		dev_err(hsotg->dev, "Core isn't in DWC2_L1 state\n");
		return;
	}

	glpmcfg = dwc2_readl(hsotg, GLPMCFG);
	if (dwc2_is_device_mode(hsotg)) {
		dev_dbg(hsotg->dev, "Exit from L1 state\n");
		glpmcfg &= ~GLPMCFG_ENBLSLPM;
		glpmcfg &= ~GLPMCFG_HIRD_THRES_EN;
		dwc2_writel(hsotg, glpmcfg, GLPMCFG);

		do {
			glpmcfg = dwc2_readl(hsotg, GLPMCFG);

			if (!(glpmcfg & (GLPMCFG_COREL1RES_MASK |
					 GLPMCFG_L1RESUMEOK | GLPMCFG_SLPSTS)))
				break;

			udelay(1);
		} while (++i < 200);

		if (i == 200) {
			dev_err(hsotg->dev, "Failed to exit L1 sleep state in 200us.\n");
			return;
		}
		dwc2_gadget_init_lpm(hsotg);
	} else {
		/* TODO */
		dev_err(hsotg->dev, "Host side LPM is not supported.\n");
		return;
	}

	/* Change to L0 state */
	hsotg->lx_state = DWC2_L0;

	/* Inform gadget to exit from L1 */
	call_gadget(hsotg, resume);
}