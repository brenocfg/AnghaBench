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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  deb_xfer (char*,int) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*,int)) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int s6x0_i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int s6x0_read_mac_address(struct dvb_usb_device *d, u8 mac[6])
{
	int i, ret;
	u8 ibuf[] = { 0 }, obuf[] = { 0 };
	u8 eeprom[256], eepromline[16];
	struct i2c_msg msg[] = {
		{
			.addr = 0xa0 >> 1,
			.flags = 0,
			.buf = obuf,
			.len = 1,
		}, {
			.addr = 0xa0 >> 1,
			.flags = I2C_M_RD,
			.buf = ibuf,
			.len = 1,
		}
	};

	for (i = 0; i < 256; i++) {
		obuf[0] = i;
		ret = s6x0_i2c_transfer(&d->i2c_adap, msg, 2);
		if (ret != 2) {
			err("read eeprom failed.");
			return -1;
		} else {
			eepromline[i % 16] = ibuf[0];
			eeprom[i] = ibuf[0];
		}

		if ((i % 16) == 15) {
			deb_xfer("%02x: ", i - 15);
			debug_dump(eepromline, 16, deb_xfer);
		}
	}

	memcpy(mac, eeprom + 16, 6);
	return 0;
}