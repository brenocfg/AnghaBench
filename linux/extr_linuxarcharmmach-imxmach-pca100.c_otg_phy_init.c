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
struct platform_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_EHCI_INTERFACE_DIFF_UNI ; 
 int /*<<< orphan*/  OTG_PHY_CS_GPIO ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mx27_initialize_usb_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otg_phy_init(struct platform_device *pdev)
{
	gpio_set_value(OTG_PHY_CS_GPIO, 0);

	mdelay(10);

	return mx27_initialize_usb_hw(pdev->id, MXC_EHCI_INTERFACE_DIFF_UNI);
}