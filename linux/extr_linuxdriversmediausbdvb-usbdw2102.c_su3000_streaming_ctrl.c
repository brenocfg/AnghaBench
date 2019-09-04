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
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SU3000_STREAM_CTRL ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int su3000_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	static u8 command_start[] = {0x00};
	static u8 command_stop[] = {0x01};
	struct i2c_msg msg = {
		.addr = SU3000_STREAM_CTRL,
		.flags = 0,
		.buf = onoff ? command_start : command_stop,
		.len = 1
	};

	i2c_transfer(&adap->dev->i2c_adap, &msg, 1);

	return 0;
}