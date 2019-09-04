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
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  IOMUX_CONFIG_GPIO ; 
 int /*<<< orphan*/  IOMUX_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUX_PGP_UH2 ; 
 int /*<<< orphan*/  MX31_PIN_DTR_DCE1 ; 
 int /*<<< orphan*/  MX31_PIN_SCK3 ; 
 int /*<<< orphan*/  MX31_PIN_SFS3 ; 
 int /*<<< orphan*/  MX31_PIN_SRXD3 ; 
 int /*<<< orphan*/  MX31_PIN_SRXD6 ; 
 int /*<<< orphan*/  MX31_PIN_STXD3 ; 
 int /*<<< orphan*/  MX31_PIN_STXD6 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_CLK ; 
 int MX31_PIN_USBH2_CLK__USBH2_CLK ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DATA0 ; 
 int MX31_PIN_USBH2_DATA0__USBH2_DATA0 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DATA1 ; 
 int MX31_PIN_USBH2_DATA1__USBH2_DATA1 ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_DIR ; 
 int MX31_PIN_USBH2_DIR__USBH2_DIR ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_NXT ; 
 int MX31_PIN_USBH2_NXT__USBH2_NXT ; 
 int /*<<< orphan*/  MX31_PIN_USBH2_STP ; 
 int MX31_PIN_USBH2_STP__USBH2_STP ; 
 int /*<<< orphan*/  MXC_EHCI_POWER_PINS_ENABLED ; 
 int /*<<< orphan*/  USB_PAD_CFG ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mx31_initialize_usb_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_iomux_alloc_pin (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mxc_iomux_set_gpr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_iomux_set_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_iomux_setup_multiple_pins (int*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int usbh2_init(struct platform_device *pdev)
{
	int pins[] = {
		MX31_PIN_USBH2_DATA0__USBH2_DATA0,
		MX31_PIN_USBH2_DATA1__USBH2_DATA1,
		MX31_PIN_USBH2_CLK__USBH2_CLK,
		MX31_PIN_USBH2_DIR__USBH2_DIR,
		MX31_PIN_USBH2_NXT__USBH2_NXT,
		MX31_PIN_USBH2_STP__USBH2_STP,
	};

	mxc_iomux_setup_multiple_pins(pins, ARRAY_SIZE(pins), "USB H2");

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

	/* chip select */
	mxc_iomux_alloc_pin(IOMUX_MODE(MX31_PIN_DTR_DCE1, IOMUX_CONFIG_GPIO),
				"USBH2_CS");
	gpio_request(IOMUX_TO_GPIO(MX31_PIN_DTR_DCE1), "USBH2 CS");
	gpio_direction_output(IOMUX_TO_GPIO(MX31_PIN_DTR_DCE1), 0);

	mdelay(10);

	return mx31_initialize_usb_hw(pdev->id, MXC_EHCI_POWER_PINS_ENABLED);
}