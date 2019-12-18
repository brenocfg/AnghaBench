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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct dvb_frontend {TYPE_2__* dvb; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_4__ {struct dvb_usb_adapter* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int az6027_set_voltage(struct dvb_frontend *fe,
			      enum fe_sec_voltage voltage)
{

	u8 buf;
	struct dvb_usb_adapter *adap = fe->dvb->priv;

	struct i2c_msg i2c_msg = {
		.addr	= 0x99,
		.flags	= 0,
		.buf	= &buf,
		.len	= 1
	};

	/*
	 * 2   --18v
	 * 1   --13v
	 * 0   --off
	 */
	switch (voltage) {
	case SEC_VOLTAGE_13:
		buf = 1;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		break;

	case SEC_VOLTAGE_18:
		buf = 2;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		break;

	case SEC_VOLTAGE_OFF:
		buf = 0;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}