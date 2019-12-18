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
struct brcm_usb_init_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CTL ; 
 int /*<<< orphan*/  PLL_IDDQ_PWRDN ; 
 scalar_t__ USB_CTRL_MASK_FAMILY (struct brcm_usb_init_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CTRL_SET_FAMILY (struct brcm_usb_init_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PM ; 
 int /*<<< orphan*/  USB_PWRDN ; 

void brcm_usb_uninit_common(struct brcm_usb_init_params *params)
{
	if (USB_CTRL_MASK_FAMILY(params, USB_PM, USB_PWRDN))
		USB_CTRL_SET_FAMILY(params, USB_PM, USB_PWRDN);

	if (USB_CTRL_MASK_FAMILY(params, PLL_CTL, PLL_IDDQ_PWRDN))
		USB_CTRL_SET_FAMILY(params, PLL_CTL, PLL_IDDQ_PWRDN);
}