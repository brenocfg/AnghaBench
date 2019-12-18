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
struct dwc2_hsotg {scalar_t__ lx_state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DWC2_L2 ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GINTSTS ; 
 int /*<<< orphan*/  GINTSTS_SESSREQINT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc2_exit_partial_power_down (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_hsotg_disconnect (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_is_device_mode (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_handle_session_req_intr(struct dwc2_hsotg *hsotg)
{
	int ret;

	/* Clear interrupt */
	dwc2_writel(hsotg, GINTSTS_SESSREQINT, GINTSTS);

	dev_dbg(hsotg->dev, "Session request interrupt - lx_state=%d\n",
		hsotg->lx_state);

	if (dwc2_is_device_mode(hsotg)) {
		if (hsotg->lx_state == DWC2_L2) {
			ret = dwc2_exit_partial_power_down(hsotg, true);
			if (ret && (ret != -ENOTSUPP))
				dev_err(hsotg->dev,
					"exit power_down failed\n");
		}

		/*
		 * Report disconnect if there is any previous session
		 * established
		 */
		dwc2_hsotg_disconnect(hsotg);
	}
}