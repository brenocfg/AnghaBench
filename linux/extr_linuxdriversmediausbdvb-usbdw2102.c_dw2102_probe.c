#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_5__ {void* rc_codes; void* rc_query; } ;
struct TYPE_6__ {TYPE_1__ core; } ;
struct dvb_usb_device_properties {int num_device_descs; TYPE_4__* adapter; int /*<<< orphan*/ * devices; TYPE_2__ rc; int /*<<< orphan*/  firmware; } ;
struct TYPE_8__ {TYPE_3__* fe; } ;
struct TYPE_7__ {int /*<<< orphan*/  frontend_attach; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P1100_FIRMWARE ; 
 int /*<<< orphan*/  P7500_FIRMWARE ; 
 void* RC_MAP_TBS_NEC ; 
 int /*<<< orphan*/  S660_FIRMWARE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  d1100 ; 
 int /*<<< orphan*/  d421 ; 
 int /*<<< orphan*/  d480_1 ; 
 int /*<<< orphan*/  d480_2 ; 
 int /*<<< orphan*/  d632 ; 
 int /*<<< orphan*/  d660 ; 
 int /*<<< orphan*/  d7500 ; 
 int /*<<< orphan*/  ds3000_frontend_attach ; 
 scalar_t__ dvb_usb_device_init (struct usb_interface*,struct dvb_usb_device_properties*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dvb_usb_device_properties dw2102_properties ; 
 struct dvb_usb_device_properties dw2104_properties ; 
 struct dvb_usb_device_properties dw3101_properties ; 
 int /*<<< orphan*/  kfree (struct dvb_usb_device_properties*) ; 
 struct dvb_usb_device_properties* kmemdup (struct dvb_usb_device_properties*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m88rs2000_frontend_attach ; 
 int /*<<< orphan*/  prof_7500_frontend_attach ; 
 void* prof_rc_query ; 
 struct dvb_usb_device_properties s6x0_properties ; 
 int /*<<< orphan*/  stv0288_frontend_attach ; 
 struct dvb_usb_device_properties su3000_properties ; 
 struct dvb_usb_device_properties t220_properties ; 
 struct dvb_usb_device_properties tt_s2_4600_properties ; 

__attribute__((used)) static int dw2102_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	int retval = -ENOMEM;
	struct dvb_usb_device_properties *p1100;
	struct dvb_usb_device_properties *s660;
	struct dvb_usb_device_properties *p7500;
	struct dvb_usb_device_properties *s421;

	p1100 = kmemdup(&s6x0_properties,
			sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!p1100)
		goto err0;

	/* copy default structure */
	/* fill only different fields */
	p1100->firmware = P1100_FIRMWARE;
	p1100->devices[0] = d1100;
	p1100->rc.core.rc_query = prof_rc_query;
	p1100->rc.core.rc_codes = RC_MAP_TBS_NEC;
	p1100->adapter->fe[0].frontend_attach = stv0288_frontend_attach;

	s660 = kmemdup(&s6x0_properties,
		       sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!s660)
		goto err1;

	s660->firmware = S660_FIRMWARE;
	s660->num_device_descs = 3;
	s660->devices[0] = d660;
	s660->devices[1] = d480_1;
	s660->devices[2] = d480_2;
	s660->adapter->fe[0].frontend_attach = ds3000_frontend_attach;

	p7500 = kmemdup(&s6x0_properties,
			sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!p7500)
		goto err2;

	p7500->firmware = P7500_FIRMWARE;
	p7500->devices[0] = d7500;
	p7500->rc.core.rc_query = prof_rc_query;
	p7500->rc.core.rc_codes = RC_MAP_TBS_NEC;
	p7500->adapter->fe[0].frontend_attach = prof_7500_frontend_attach;


	s421 = kmemdup(&su3000_properties,
		       sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!s421)
		goto err3;

	s421->num_device_descs = 2;
	s421->devices[0] = d421;
	s421->devices[1] = d632;
	s421->adapter->fe[0].frontend_attach = m88rs2000_frontend_attach;

	if (0 == dvb_usb_device_init(intf, &dw2102_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &dw2104_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &dw3101_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &s6x0_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, p1100,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, s660,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, p7500,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, s421,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &su3000_properties,
			 THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &t220_properties,
			 THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &tt_s2_4600_properties,
			 THIS_MODULE, NULL, adapter_nr)) {

		/* clean up copied properties */
		kfree(s421);
		kfree(p7500);
		kfree(s660);
		kfree(p1100);

		return 0;
	}

	retval = -ENODEV;
	kfree(s421);
err3:
	kfree(p7500);
err2:
	kfree(s660);
err1:
	kfree(p1100);
err0:
	return retval;
}