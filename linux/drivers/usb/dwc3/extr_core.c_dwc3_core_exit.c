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
struct dwc3 {int /*<<< orphan*/  reset; int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; int /*<<< orphan*/  usb3_generic_phy; int /*<<< orphan*/  usb2_generic_phy; int /*<<< orphan*/  usb3_phy; int /*<<< orphan*/  usb2_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_event_buffers_cleanup (struct dwc3*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_phy_set_suspend (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_core_exit(struct dwc3 *dwc)
{
	dwc3_event_buffers_cleanup(dwc);

	usb_phy_shutdown(dwc->usb2_phy);
	usb_phy_shutdown(dwc->usb3_phy);
	phy_exit(dwc->usb2_generic_phy);
	phy_exit(dwc->usb3_generic_phy);

	usb_phy_set_suspend(dwc->usb2_phy, 1);
	usb_phy_set_suspend(dwc->usb3_phy, 1);
	phy_power_off(dwc->usb2_generic_phy);
	phy_power_off(dwc->usb3_generic_phy);
	clk_bulk_disable_unprepare(dwc->num_clks, dwc->clks);
	reset_control_assert(dwc->reset);
}