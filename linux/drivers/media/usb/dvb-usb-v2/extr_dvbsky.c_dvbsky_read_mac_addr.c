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
struct dvb_usb_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int dvbsky_read_mac_addr(struct dvb_usb_adapter *adap, u8 mac[6])
{
	struct dvb_usb_device *d = adap_to_d(adap);
	u8 obuf[] = { 0x1e, 0x00 };
	u8 ibuf[6] = { 0 };
	struct i2c_msg msg[] = {
		{
			.addr = 0x51,
			.flags = 0,
			.buf = obuf,
			.len = 2,
		}, {
			.addr = 0x51,
			.flags = I2C_M_RD,
			.buf = ibuf,
			.len = 6,
		}
	};

	if (i2c_transfer(&d->i2c_adap, msg, 2) == 2)
		memcpy(mac, ibuf, 6);

	return 0;
}