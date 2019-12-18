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
struct dvb_usb_adapter {TYPE_4__* fe_adap; TYPE_1__* dev; } ;
struct TYPE_8__ {TYPE_3__* fe; } ;
struct TYPE_6__ {int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  tda10023_attach ; 
 int /*<<< orphan*/  tda10023_config ; 
 int /*<<< orphan*/  tda10048_attach ; 
 int /*<<< orphan*/  tda10048_config ; 
 int /*<<< orphan*/  tt3650_ci_init (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  ttusb2_ct3650_i2c_gate_ctrl ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ttusb2_frontend_tda10023_attach(struct dvb_usb_adapter *adap)
{
	if (usb_set_interface(adap->dev->udev, 0, 3) < 0)
		err("set interface to alts=3 failed");

	if (adap->fe_adap[0].fe == NULL) {
		/* FE 0 DVB-C */
		adap->fe_adap[0].fe = dvb_attach(tda10023_attach,
			&tda10023_config, &adap->dev->i2c_adap, 0x48);

		if (adap->fe_adap[0].fe == NULL) {
			deb_info("TDA10023 attach failed\n");
			return -ENODEV;
		}
		tt3650_ci_init(adap);
	} else {
		adap->fe_adap[1].fe = dvb_attach(tda10048_attach,
			&tda10048_config, &adap->dev->i2c_adap);

		if (adap->fe_adap[1].fe == NULL) {
			deb_info("TDA10048 attach failed\n");
			return -ENODEV;
		}

		/* tuner is behind TDA10023 I2C-gate */
		adap->fe_adap[1].fe->ops.i2c_gate_ctrl = ttusb2_ct3650_i2c_gate_ctrl;

	}

	return 0;
}