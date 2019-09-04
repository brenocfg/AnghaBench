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
 int /*<<< orphan*/  MX31_PIN_IOIS16 ; 
 int /*<<< orphan*/  MX31_PIN_PC_BVD1 ; 
 int /*<<< orphan*/  MX31_PIN_PC_BVD2 ; 
 int /*<<< orphan*/  MX31_PIN_PC_RST ; 
 int /*<<< orphan*/  MX31_PIN_PC_RW_B ; 
 int /*<<< orphan*/  MX31_PIN_PC_VS2 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_CLK ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DATA0 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DATA1 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DIR ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_NXT ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_STP ; 
 int /*<<< orphan*/  MXC_EHCI_POWER_PINS_ENABLED ; 
 int /*<<< orphan*/  USBH2_RST_B ; 
 int /*<<< orphan*/  USB_PAD_CFG ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mx31_initialize_usb_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_iomux_set_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int mx31_3ds_host2_init(struct platform_device *pdev)
{
	int err;

	mxc_iomux_set_pad(MX31_PIN_USBH2_CLK, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_DIR, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_NXT, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_STP, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_DATA0, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_DATA1, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_PC_VS2, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_PC_BVD1, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_PC_BVD2, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_PC_RST, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_IOIS16, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_PC_RW_B, USB_PAD_CFG);

	err = gpio_request(USBH2_RST_B, "usbh2-reset");
	if (err) {
		pr_err("Failed to request the USB Host 2 reset gpio\n");
		return err;
	}

	err = gpio_direction_output(USBH2_RST_B, 0);
	if (err) {
		pr_err("Failed to drive the USB Host 2 reset gpio\n");
		goto usbotg_free_reset;
	}

	mdelay(1);
	gpio_set_value(USBH2_RST_B, 1);

	mdelay(10);

	return mx31_initialize_usb_hw(pdev->id, MXC_EHCI_POWER_PINS_ENABLED);

usbotg_free_reset:
	gpio_free(USBH2_RST_B);
	return err;
}