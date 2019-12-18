#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {TYPE_2__* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_8PSK ; 
 int EINVAL ; 
 int USB_PID_GENPIX_8PSK_REV_1_WARM ; 
 int /*<<< orphan*/  deb_xfer (char*) ; 
 scalar_t__ gp8psk_load_bcm4500fw (struct dvb_usb_device*) ; 
 scalar_t__ gp8psk_usb_in_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_bcm4500_reload(struct dvb_usb_device *d)
{
	u8 buf;
	int gp_product_id = le16_to_cpu(d->udev->descriptor.idProduct);

	deb_xfer("reloading firmware\n");

	/* Turn off 8psk power */
	if (gp8psk_usb_in_op(d, BOOT_8PSK, 0, 0, &buf, 1))
		return -EINVAL;
	/* Turn On 8psk power */
	if (gp8psk_usb_in_op(d, BOOT_8PSK, 1, 0, &buf, 1))
		return -EINVAL;
	/* load BCM4500 firmware */
	if (gp_product_id == USB_PID_GENPIX_8PSK_REV_1_WARM)
		if (gp8psk_load_bcm4500fw(d))
			return -EINVAL;
	return 0;
}