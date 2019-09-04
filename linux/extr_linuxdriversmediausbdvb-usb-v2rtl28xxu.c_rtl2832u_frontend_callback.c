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
struct rtl28xxu_dev {int /*<<< orphan*/  tuner; } ;
struct TYPE_4__ {struct device* parent; } ;
struct i2c_adapter {TYPE_2__ dev; } ;
struct dvb_usb_device {TYPE_1__* intf; struct rtl28xxu_dev* priv; } ;
struct device {int /*<<< orphan*/ * type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DVB_FRONTEND_COMPONENT_TUNER 130 
 int EINVAL ; 
#define  TUNER_RTL2832_FC0012 129 
#define  TUNER_RTL2832_TUA9001 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  i2c_adapter_type ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int rtl2832u_fc0012_tuner_callback (struct dvb_usb_device*,int,int) ; 
 int rtl2832u_tua9001_tuner_callback (struct dvb_usb_device*,int,int) ; 
 struct i2c_adapter* to_i2c_adapter (struct device*) ; 

__attribute__((used)) static int rtl2832u_frontend_callback(void *adapter_priv, int component,
		int cmd, int arg)
{
	struct i2c_adapter *adapter = adapter_priv;
	struct device *parent = adapter->dev.parent;
	struct i2c_adapter *parent_adapter;
	struct dvb_usb_device *d;
	struct rtl28xxu_dev *dev;

	/*
	 * All tuners are connected to demod muxed I2C adapter. We have to
	 * resolve its parent adapter in order to get handle for this driver
	 * private data. That is a bit hackish solution, GPIO or direct driver
	 * callback would be better...
	 */
	if (parent != NULL && parent->type == &i2c_adapter_type)
		parent_adapter = to_i2c_adapter(parent);
	else
		return -EINVAL;

	d = i2c_get_adapdata(parent_adapter);
	dev = d->priv;

	dev_dbg(&d->intf->dev, "component=%d cmd=%d arg=%d\n",
		component, cmd, arg);

	switch (component) {
	case DVB_FRONTEND_COMPONENT_TUNER:
		switch (dev->tuner) {
		case TUNER_RTL2832_FC0012:
			return rtl2832u_fc0012_tuner_callback(d, cmd, arg);
		case TUNER_RTL2832_TUA9001:
			return rtl2832u_tua9001_tuner_callback(d, cmd, arg);
		}
	}

	return 0;
}