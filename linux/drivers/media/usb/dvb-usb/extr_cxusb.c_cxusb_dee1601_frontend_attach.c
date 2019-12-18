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
struct dvb_usb_adapter {TYPE_1__* fe_adap; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  udev; } ;
struct TYPE_3__ {void* fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DIGITAL ; 
 int EIO ; 
 int /*<<< orphan*/  cxusb_ctrl_msg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_dee1601_config ; 
 int /*<<< orphan*/  cxusb_zl10353_dee1601_config ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mt352_attach ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zl10353_attach ; 

__attribute__((used)) static int cxusb_dee1601_frontend_attach(struct dvb_usb_adapter *adap)
{
	if (usb_set_interface(adap->dev->udev, 0, 0) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, NULL, 0, NULL, 0);

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &cxusb_dee1601_config,
					 &adap->dev->i2c_adap);
	if (adap->fe_adap[0].fe)
		return 0;

	adap->fe_adap[0].fe = dvb_attach(zl10353_attach,
					 &cxusb_zl10353_dee1601_config,
					 &adap->dev->i2c_adap);
	if (adap->fe_adap[0].fe)
		return 0;

	return -EIO;
}