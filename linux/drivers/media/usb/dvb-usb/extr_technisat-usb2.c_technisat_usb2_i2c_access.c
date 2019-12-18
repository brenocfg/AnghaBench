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
typedef  int u8 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_SPEED_100KHZ_BIT ; 
 int I2C_STATUS_NAK ; 
 int I2C_STATUS_OK ; 
 int /*<<< orphan*/  deb_i2c (char*,...) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  err (char*,int,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int technisat_usb2_i2c_access(struct usb_device *udev,
		u8 device_addr, u8 *tx, u8 txlen, u8 *rx, u8 rxlen)
{
	u8 *b;
	int ret, actual_length;

	b = kmalloc(64, GFP_KERNEL);
	if (!b)
		return -ENOMEM;

	deb_i2c("i2c-access: %02x, tx: ", device_addr);
	debug_dump(tx, txlen, deb_i2c);
	deb_i2c(" ");

	if (txlen > 62) {
		err("i2c TX buffer can't exceed 62 bytes (dev 0x%02x)",
				device_addr);
		txlen = 62;
	}
	if (rxlen > 62) {
		err("i2c RX buffer can't exceed 62 bytes (dev 0x%02x)",
				device_addr);
		rxlen = 62;
	}

	b[0] = I2C_SPEED_100KHZ_BIT;
	b[1] = device_addr << 1;

	if (rx != NULL) {
		b[0] |= rxlen;
		b[1] |= 1;
	}

	memcpy(&b[2], tx, txlen);
	ret = usb_bulk_msg(udev,
			usb_sndbulkpipe(udev, 0x01),
			b, 2 + txlen,
			NULL, 1000);

	if (ret < 0) {
		err("i2c-error: out failed %02x = %d", device_addr, ret);
		goto err;
	}

	ret = usb_bulk_msg(udev,
			usb_rcvbulkpipe(udev, 0x01),
			b, 64, &actual_length, 1000);
	if (ret < 0) {
		err("i2c-error: in failed %02x = %d", device_addr, ret);
		goto err;
	}

	if (b[0] != I2C_STATUS_OK) {
		err("i2c-error: %02x = %d", device_addr, b[0]);
		/* handle tuner-i2c-nak */
		if (!(b[0] == I2C_STATUS_NAK &&
				device_addr == 0x60
				/* && device_is_technisat_usb2 */))
			goto err;
	}

	deb_i2c("status: %d, ", b[0]);

	if (rx != NULL) {
		memcpy(rx, &b[2], rxlen);

		deb_i2c("rx (%d): ", rxlen);
		debug_dump(rx, rxlen, deb_i2c);
	}

	deb_i2c("\n");

err:
	kfree(b);
	return ret;
}