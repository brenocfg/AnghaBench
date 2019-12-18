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
struct usb_device_id {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct dvb_usb_adapter {TYPE_3__* dev; TYPE_1__* fe_adap; } ;
struct TYPE_6__ {TYPE_2__* desc; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_5__ {struct usb_device_id** warm_ids; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ USB_PID_TECHNOTREND_CONNECT_S2_3650_CI ; 
 scalar_t__ USB_VID_TECHNOTREND ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  lnbp22_attach ; 
 int /*<<< orphan*/  stb0899_attach ; 
 int /*<<< orphan*/  stb0899_config ; 
 int /*<<< orphan*/  tt3650_ci_init (struct dvb_usb_adapter*) ; 

__attribute__((used)) static int pctv452e_frontend_attach(struct dvb_usb_adapter *a)
{
	struct usb_device_id *id;

	a->fe_adap[0].fe = dvb_attach(stb0899_attach, &stb0899_config,
						&a->dev->i2c_adap);
	if (!a->fe_adap[0].fe)
		return -ENODEV;
	if ((dvb_attach(lnbp22_attach, a->fe_adap[0].fe,
					&a->dev->i2c_adap)) == NULL)
		err("Cannot attach lnbp22\n");

	id = a->dev->desc->warm_ids[0];
	if (USB_VID_TECHNOTREND == id->idVendor
	    && USB_PID_TECHNOTREND_CONNECT_S2_3650_CI == id->idProduct)
		/* Error ignored. */
		tt3650_ci_init(a);

	return 0;
}