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
 int /*<<< orphan*/  MUX_PGP_USB_SUSPEND ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_MISO ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_MOSI ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_SCLK ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_SPI_RDY ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_SS0 ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_SS1 ; 
 int /*<<< orphan*/  MX31_PIN_CSPI1_SS2 ; 
 int /*<<< orphan*/  MX31_PIN_SFS6 ; 
 int MXC_EHCI_INTERFACE_SINGLE_UNI ; 
 int MXC_EHCI_POWER_PINS_ENABLED ; 
 int /*<<< orphan*/  USB_PAD_CFG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mx31_initialize_usb_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_iomux_set_gpr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_iomux_set_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marxbot_usbh1_hw_init(struct platform_device *pdev)
{
	mxc_iomux_set_gpr(MUX_PGP_USB_SUSPEND, true);

	mxc_iomux_set_pad(MX31_PIN_CSPI1_MISO, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_CSPI1_MOSI, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_CSPI1_SS0, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_CSPI1_SS1, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_CSPI1_SS2, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_CSPI1_SCLK, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_CSPI1_SPI_RDY, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SFS6, USB_PAD_CFG);

	mdelay(10);

	return mx31_initialize_usb_hw(pdev->id, MXC_EHCI_POWER_PINS_ENABLED |
			MXC_EHCI_INTERFACE_SINGLE_UNI);
}