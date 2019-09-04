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

__attribute__((used)) static int opera1_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	static u8 buf_start[2] = { 0xff, 0x03 };
	static u8 buf_stop[2] = { 0xff, 0x00 };
	struct i2c_msg start_tuner[] = {
		{.addr = ADDR_B1A6_STREAM_CTRL,.buf = onoff ? buf_start : buf_stop,.len = 2},
	};
	if (dvb_usb_opera1_debug)
		info("streaming %s", onoff ? "on" : "off");
	i2c_transfer(&adap->dev->i2c_adap, start_tuner, 1);
	return 0;
}