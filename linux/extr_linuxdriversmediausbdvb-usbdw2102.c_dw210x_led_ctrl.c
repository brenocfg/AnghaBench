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
typedef  int u8 ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_usb_adapter {TYPE_2__* dev; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW2102_LED_CTRL ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static void dw210x_led_ctrl(struct dvb_frontend *fe, int offon)
{
	static u8 led_off[] = { 0 };
	static u8 led_on[] = { 1 };
	struct i2c_msg msg = {
		.addr = DW2102_LED_CTRL,
		.flags = 0,
		.buf = led_off,
		.len = 1
	};
	struct dvb_usb_adapter *udev_adap =
		(struct dvb_usb_adapter *)(fe->dvb->priv);

	if (offon)
		msg.buf = led_on;
	i2c_transfer(&udev_adap->dev->i2c_adap, &msg, 1);
}