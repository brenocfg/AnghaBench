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
struct dvb_usb_adapter {TYPE_1__* dev; TYPE_2__* fe_adap; } ;
struct TYPE_4__ {int /*<<< orphan*/  fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lnbp21_attach ; 
 int /*<<< orphan*/  tda826x_attach ; 

__attribute__((used)) static int ttusb2_tuner_tda826x_attach(struct dvb_usb_adapter *adap)
{
	if (dvb_attach(tda826x_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap, 0) == NULL) {
		deb_info("TDA8263 attach failed\n");
		return -ENODEV;
	}

	if (dvb_attach(lnbp21_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap, 0, 0) == NULL) {
		deb_info("LNBP21 attach failed\n");
		return -ENODEV;
	}
	return 0;
}