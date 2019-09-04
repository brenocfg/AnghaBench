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
 int /*<<< orphan*/  MUX_PGP_UH2 ; 
 int /*<<< orphan*/  MX31_PIN_SCK3 ; 
 int /*<<< orphan*/  MX31_PIN_SFS3 ; 
 int /*<<< orphan*/  MX31_PIN_SRXD3 ; 
 int /*<<< orphan*/  MX31_PIN_SRXD6 ; 
 int /*<<< orphan*/  MX31_PIN_STXD3 ; 
 int /*<<< orphan*/  MX31_PIN_STXD6 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_CLK ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DATA0 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DATA1 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DIR ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_NXT ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_STP ; 
 int MXC_EHCI_INTERFACE_DIFF_UNI ; 
 int MXC_EHCI_POWER_PINS_ENABLED ; 
 int /*<<< orphan*/  USBH2_CS ; 
 int /*<<< orphan*/  USBH2_RESET ; 
 int /*<<< orphan*/  USB_PAD_CFG ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mx31_initialize_usb_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_iomux_set_gpr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_iomux_set_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int usbh2_init(struct platform_device *pdev)
{
	int err;

	mxc_iomux_set_pad(MX31_PIN_USBH2_CLK, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_DIR, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_NXT, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_STP, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_DATA0, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_USBH2_DATA1, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SRXD6, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_STXD6, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SFS3, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SCK3, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SRXD3, USB_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_STXD3, USB_PAD_CFG);

	mxc_iomux_set_gpr(MUX_PGP_UH2, true);


	/* Enable the chip */
	err = gpio_request(USBH2_CS, "USB-H2-CS");
	if (err) {
		pr_err("Failed to request the usb host 2 CS gpio\n");
		return err;
	}

	err = gpio_direction_output(USBH2_CS, 0/*Enabled*/);
	if (err) {
		pr_err("Failed to drive the usb host 2 CS gpio\n");
		goto h2_free_cs;
	}

	/* H2 phy reset*/
	err = gpio_request(USBH2_RESET, "USB-H2-RESET");
	if (err) {
		pr_err("Failed to request the usb host 2 reset gpio\n");
		goto h2_free_cs;
	}

	err = gpio_direction_output(USBH2_RESET, 1/*HIGH*/);
	if (err) {
		pr_err("Failed to reset the usb host 2 phy\n");
		goto h2_free_reset;
	}

	gpio_set_value(USBH2_RESET, 0/*LOW*/);
	mdelay(5);
	gpio_set_value(USBH2_RESET, 1/*HIGH*/);
	mdelay(10);

	return mx31_initialize_usb_hw(pdev->id, MXC_EHCI_POWER_PINS_ENABLED |
			MXC_EHCI_INTERFACE_DIFF_UNI);

h2_free_reset:
	gpio_free(USBH2_RESET);
h2_free_cs:
	gpio_free(USBH2_CS);
	return err;
}