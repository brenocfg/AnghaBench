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
struct dvb_usb_adapter {TYPE_2__* dev; TYPE_1__* fe_adap; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  udev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  tda10086_attach ; 
 int /*<<< orphan*/  tda10086_config ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ttusb2_frontend_tda10086_attach(struct dvb_usb_adapter *adap)
{
	if (usb_set_interface(adap->dev->udev,0,3) < 0)
		err("set interface to alts=3 failed");

	if ((adap->fe_adap[0].fe = dvb_attach(tda10086_attach, &tda10086_config, &adap->dev->i2c_adap)) == NULL) {
		deb_info("TDA10086 attach failed\n");
		return -ENODEV;
	}

	return 0;
}