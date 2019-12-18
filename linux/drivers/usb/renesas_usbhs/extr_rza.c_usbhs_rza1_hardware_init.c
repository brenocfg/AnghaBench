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
typedef  scalar_t__ u32 ;
struct usbhs_priv {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SUSPM ; 
 int /*<<< orphan*/  SUSPMODE ; 
 int /*<<< orphan*/  SYSCFG ; 
 int /*<<< orphan*/  UCKSEL ; 
 int /*<<< orphan*/  UPLLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usbhs_priv* usbhs_pdev_to_priv (struct platform_device*) ; 
 int /*<<< orphan*/  usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int usbhs_rza1_hardware_init(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	struct device_node *usb_x1_clk, *extal_clk;
	u32 freq_usb = 0, freq_extal = 0;

	/* Input Clock Selection (NOTE: ch0 controls both ch0 and ch1) */
	usb_x1_clk = of_find_node_by_name(NULL, "usb_x1");
	extal_clk = of_find_node_by_name(NULL, "extal");
	of_property_read_u32(usb_x1_clk, "clock-frequency", &freq_usb);
	of_property_read_u32(extal_clk, "clock-frequency", &freq_extal);
	if (freq_usb == 0) {
		if (freq_extal == 12000000) {
			/* Select 12MHz XTAL */
			usbhs_bset(priv, SYSCFG, UCKSEL, UCKSEL);
		} else {
			dev_err(usbhs_priv_to_dev(priv), "A 48MHz USB clock or 12MHz main clock is required.\n");
			return -EIO;
		}
	}

	/* Enable USB PLL (NOTE: ch0 controls both ch0 and ch1) */
	usbhs_bset(priv, SYSCFG, UPLLE, UPLLE);
	usleep_range(1000, 2000);
	usbhs_bset(priv, SUSPMODE, SUSPM, SUSPM);

	return 0;
}