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
struct i2c_msg {int len; unsigned char* buf; int addr; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct cx231xx {int i2c_scan_running; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 struct i2c_adapter* cx231xx_get_i2c_adap (struct cx231xx*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 char** i2c_devs ; 
 int /*<<< orphan*/  i2c_scan ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

void cx231xx_do_i2c_scan(struct cx231xx *dev, int i2c_port)
{
	unsigned char buf;
	int i, rc;
	struct i2c_adapter *adap;
	struct i2c_msg msg = {
		.flags = I2C_M_RD,
		.len = 1,
		.buf = &buf,
	};

	if (!i2c_scan)
		return;

	/* Don't generate I2C errors during scan */
	dev->i2c_scan_running = true;
	adap = cx231xx_get_i2c_adap(dev, i2c_port);

	for (i = 0; i < 128; i++) {
		msg.addr = i;
		rc = i2c_transfer(adap, &msg, 1);

		if (rc < 0)
			continue;
		dev_info(dev->dev,
			 "i2c scan: found device @ port %d addr 0x%x  [%s]\n",
			 i2c_port,
			 i << 1,
			 i2c_devs[i] ? i2c_devs[i] : "???");
	}

	dev->i2c_scan_running = false;
}