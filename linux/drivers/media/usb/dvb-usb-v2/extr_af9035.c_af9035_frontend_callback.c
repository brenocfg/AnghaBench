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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;

/* Variables and functions */
#define  DVB_FRONTEND_COMPONENT_TUNER 128 
 int af9035_tuner_callback (struct dvb_usb_device*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int af9035_frontend_callback(void *adapter_priv, int component,
				    int cmd, int arg)
{
	struct i2c_adapter *adap = adapter_priv;
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct usb_interface *intf = d->intf;

	dev_dbg(&intf->dev, "component=%d cmd=%d arg=%d\n",
		component, cmd, arg);

	switch (component) {
	case DVB_FRONTEND_COMPONENT_TUNER:
		return af9035_tuner_callback(d, cmd, arg);
	default:
		break;
	}

	return 0;
}