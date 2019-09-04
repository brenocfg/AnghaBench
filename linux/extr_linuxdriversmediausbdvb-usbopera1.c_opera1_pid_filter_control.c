#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  addr; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_B1A6_STREAM_CTRL ; 
 scalar_t__ dvb_usb_opera1_debug ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  info (char*,char*) ; 

__attribute__((used)) static int opera1_pid_filter_control(struct dvb_usb_adapter *adap, int onoff)
{
	int u = 0x04;
	u8 b_pid[3];
	struct i2c_msg msg[] = {
		{.addr = ADDR_B1A6_STREAM_CTRL,.buf = b_pid,.len = 3},
	};
	if (dvb_usb_opera1_debug)
		info("%s hw-pidfilter", onoff ? "enable" : "disable");
	for (; u < 0x7e; u += 2) {
		b_pid[0] = u;
		b_pid[1] = 0;
		b_pid[2] = 0x80;
		i2c_transfer(&adap->dev->i2c_adap, msg, 1);
	}
	return 0;
}