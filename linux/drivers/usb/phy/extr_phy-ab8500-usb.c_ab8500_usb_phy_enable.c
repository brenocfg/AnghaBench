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
typedef  int /*<<< orphan*/  u8 ;
struct ab8500_usb {int /*<<< orphan*/  dev; int /*<<< orphan*/  sysclk; int /*<<< orphan*/  pinctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_BIT_PHY_CTRL_DEVICE_EN ; 
 int /*<<< orphan*/  AB8500_BIT_PHY_CTRL_HOST_EN ; 
 int /*<<< orphan*/  AB8500_USB ; 
 int /*<<< orphan*/  AB8500_USB_PHY_CTRL_REG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PINCTRL_STATE_DEFAULT ; 
 int /*<<< orphan*/  ab8500_usb_regulator_enable (struct ab8500_usb*) ; 
 int /*<<< orphan*/  abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pinctrl_get_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_usb_phy_enable(struct ab8500_usb *ab, bool sel_host)
{
	u8 bit;
	bit = sel_host ? AB8500_BIT_PHY_CTRL_HOST_EN :
		AB8500_BIT_PHY_CTRL_DEVICE_EN;

	/* mux and configure USB pins to DEFAULT state */
	ab->pinctrl = pinctrl_get_select(ab->dev, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(ab->pinctrl))
		dev_err(ab->dev, "could not get/set default pinstate\n");

	if (clk_prepare_enable(ab->sysclk))
		dev_err(ab->dev, "can't prepare/enable clock\n");

	ab8500_usb_regulator_enable(ab);

	abx500_mask_and_set_register_interruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			bit, bit);
}