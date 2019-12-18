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
struct dvb_usb_device {int dummy; } ;
struct dvb_usb_adapter {struct dvb_usb_device* dev; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct TYPE_2__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXUSB_OPEN_DIGITAL ; 
 int cxusb_medion_get (struct dvb_usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_medion_put (struct dvb_usb_device*) ; 

__attribute__((used)) static int cxusb_medion_fe_ts_bus_ctrl(struct dvb_frontend *fe, int acquire)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;
	struct dvb_usb_device *dvbdev = adap->dev;

	if (acquire)
		return cxusb_medion_get(dvbdev, CXUSB_OPEN_DIGITAL);

	cxusb_medion_put(dvbdev);

	return 0;
}