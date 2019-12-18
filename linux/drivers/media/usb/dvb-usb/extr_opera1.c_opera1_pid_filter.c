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
typedef  int u16 ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  addr; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_B1A6_STREAM_CTRL ; 
 scalar_t__ dvb_usb_opera1_debug ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  info (char*,int,int,char*) ; 

__attribute__((used)) static int opera1_pid_filter(struct dvb_usb_adapter *adap, int index, u16 pid,
			     int onoff)
{
	u8 b_pid[3];
	struct i2c_msg msg[] = {
		{.addr = ADDR_B1A6_STREAM_CTRL,.buf = b_pid,.len = 3},
	};
	if (dvb_usb_opera1_debug)
		info("pidfilter index: %d pid: %d %s", index, pid,
			onoff ? "on" : "off");
	b_pid[0] = (2 * index) + 4;
	b_pid[1] = onoff ? (pid & 0xff) : (0x00);
	b_pid[2] = onoff ? ((pid >> 8) & 0xff) : (0x00);
	i2c_transfer(&adap->dev->i2c_adap, msg, 1);
	return 0;
}