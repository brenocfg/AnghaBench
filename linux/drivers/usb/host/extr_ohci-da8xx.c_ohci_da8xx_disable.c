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
struct usb_hcd {int dummy; } ;
struct da8xx_ohci_hcd {int /*<<< orphan*/  usb11_clk; int /*<<< orphan*/  usb11_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct da8xx_ohci_hcd* to_da8xx_ohci (struct usb_hcd*) ; 

__attribute__((used)) static void ohci_da8xx_disable(struct usb_hcd *hcd)
{
	struct da8xx_ohci_hcd *da8xx_ohci = to_da8xx_ohci(hcd);

	phy_power_off(da8xx_ohci->usb11_phy);
	phy_exit(da8xx_ohci->usb11_phy);
	clk_disable_unprepare(da8xx_ohci->usb11_clk);
}