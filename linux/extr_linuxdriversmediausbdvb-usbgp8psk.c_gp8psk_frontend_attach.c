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
struct dvb_usb_device {TYPE_2__* udev; } ;
struct dvb_usb_adapter {TYPE_3__* fe_adap; struct dvb_usb_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  fe; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int USB_PID_GENPIX_8PSK_REV_1_WARM ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dvb_usb_device*,int) ; 
 int /*<<< orphan*/  gp8psk_fe_attach ; 
 int /*<<< orphan*/  gp8psk_fe_ops ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap->dev;
	int id = le16_to_cpu(d->udev->descriptor.idProduct);
	int is_rev1;

	is_rev1 = (id == USB_PID_GENPIX_8PSK_REV_1_WARM) ? true : false;

	adap->fe_adap[0].fe = dvb_attach(gp8psk_fe_attach,
					 &gp8psk_fe_ops, d, is_rev1);
	return 0;
}