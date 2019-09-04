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
struct usb_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBH1_MODE ; 
 int /*<<< orphan*/  USBH1_VBUSEN_B ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int devboard_isp1105_init(struct usb_phy *otg)
{
	int ret = gpio_request(USBH1_MODE, "usbh1-mode");
	if (ret)
		return ret;
	/* single ended */
	gpio_direction_output(USBH1_MODE, 0);

	ret = gpio_request(USBH1_VBUSEN_B, "usbh1-vbusen");
	if (ret) {
		gpio_free(USBH1_MODE);
		return ret;
	}
	gpio_direction_output(USBH1_VBUSEN_B, 1);

	return 0;
}