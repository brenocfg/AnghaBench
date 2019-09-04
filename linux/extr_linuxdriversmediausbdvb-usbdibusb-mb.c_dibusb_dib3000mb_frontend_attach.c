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
struct dvb_usb_adapter {TYPE_3__* fe_adap; TYPE_1__* dev; struct dibusb_state* priv; } ;
struct dibusb_state {int /*<<< orphan*/  ops; } ;
struct dib3000_config {int demod_address; } ;
struct TYPE_6__ {int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_7__ {TYPE_4__* fe; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dib3000mb_attach ; 
 int /*<<< orphan*/  dib3000mb_i2c_gate_ctrl ; 
 TYPE_4__* dvb_attach (int /*<<< orphan*/ ,struct dib3000_config*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dibusb_dib3000mb_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dib3000_config demod_cfg;
	struct dibusb_state *st = adap->priv;

	demod_cfg.demod_address = 0x8;

	adap->fe_adap[0].fe = dvb_attach(dib3000mb_attach, &demod_cfg,
					 &adap->dev->i2c_adap, &st->ops);
	if ((adap->fe_adap[0].fe) == NULL)
		return -ENODEV;

	adap->fe_adap[0].fe->ops.i2c_gate_ctrl = dib3000mb_i2c_gate_ctrl;

	return 0;
}