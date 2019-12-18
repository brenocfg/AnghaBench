#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_1__* fe_adap; TYPE_3__* dev; struct dib0700_adapter_state* priv; } ;
struct TYPE_6__ {scalar_t__ (* i2c_enumeration ) (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct dib0700_adapter_state {TYPE_2__ dib7000p_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  udev; } ;
struct TYPE_5__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DIGITAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  cxusb_bluebird_gpio_pulse (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  cxusb_ctrl_msg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_dualdig4_rev2_config ; 
 int /*<<< orphan*/  dib7000p_attach ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cxusb_dualdig4_rev2_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *state = adap->priv;

	if (usb_set_interface(adap->dev->udev, 0, 1) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, NULL, 0, NULL, 0);

	cxusb_bluebird_gpio_pulse(adap->dev, 0x02, 1);

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		return -ENODEV;

	if (state->dib7000p_ops.i2c_enumeration(&adap->dev->i2c_adap, 1, 18,
						&cxusb_dualdig4_rev2_config) < 0) {
		pr_warn("Unable to enumerate dib7000p\n");
		return -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
						       0x80,
						       &cxusb_dualdig4_rev2_config);
	if (!adap->fe_adap[0].fe)
		return -EIO;

	return 0;
}