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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct i2c_msg {int addr; scalar_t__* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 scalar_t__ technisat_usb2_calc_lrc (scalar_t__*,int) ; 

__attribute__((used)) static int technisat_usb2_eeprom_lrc_read(struct dvb_usb_device *d,
	u16 offset, u8 *b, u16 length, u8 tries)
{
	u8 bo = offset & 0xff;
	struct i2c_msg msg[] = {
		{
			.addr = 0x50 | ((offset >> 8) & 0x3),
			.buf = &bo,
			.len = 1
		}, {
			.addr = 0x50 | ((offset >> 8) & 0x3),
			.flags	= I2C_M_RD,
			.buf = b,
			.len = length
		}
	};

	while (tries--) {
		int status;

		if (i2c_transfer(&d->i2c_adap, msg, 2) != 2)
			break;

		status =
			technisat_usb2_calc_lrc(b, length - 1) == b[length - 1];

		if (status)
			return 0;
	}

	return -EREMOTEIO;
}