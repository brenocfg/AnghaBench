#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {struct platform_device** platform_device_tuner; int /*<<< orphan*/ * i2c_client; TYPE_1__* af9033_config; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct platform_device {TYPE_3__ dev; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct dvb_usb_adapter {size_t id; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int tuner; } ;

/* Variables and functions */
#define  AF9033_TUNER_FC2580 135 
#define  AF9033_TUNER_IT9135_38 134 
#define  AF9033_TUNER_IT9135_51 133 
#define  AF9033_TUNER_IT9135_52 132 
#define  AF9033_TUNER_IT9135_60 131 
#define  AF9033_TUNER_IT9135_61 130 
#define  AF9033_TUNER_IT9135_62 129 
#define  AF9033_TUNER_TUA9001 128 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  af9035_del_i2c_dev (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static int af9035_tuner_detach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	switch (state->af9033_config[adap->id].tuner) {
	case AF9033_TUNER_TUA9001:
	case AF9033_TUNER_FC2580:
		if (adap->id == 1) {
			if (state->i2c_client[3])
				af9035_del_i2c_dev(d);
		} else if (adap->id == 0) {
			if (state->i2c_client[1])
				af9035_del_i2c_dev(d);
		}
		break;
	case AF9033_TUNER_IT9135_38:
	case AF9033_TUNER_IT9135_51:
	case AF9033_TUNER_IT9135_52:
	case AF9033_TUNER_IT9135_60:
	case AF9033_TUNER_IT9135_61:
	case AF9033_TUNER_IT9135_62:
	{
		struct platform_device *pdev;

		pdev = state->platform_device_tuner[adap->id];
		if (pdev) {
			module_put(pdev->dev.driver->owner);
			platform_device_unregister(pdev);
		}
		break;
	}
	}

	return 0;
}