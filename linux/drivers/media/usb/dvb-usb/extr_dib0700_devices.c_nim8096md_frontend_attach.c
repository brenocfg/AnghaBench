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
struct dvb_frontend {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_slave_frontend ) (struct dvb_frontend*,struct dvb_frontend*) ;struct dvb_frontend* (* init ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* i2c_enumeration ) (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ;} ;
struct dib0700_adapter_state {TYPE_2__ dib8000_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_5__ {struct dvb_frontend* fe; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO0 ; 
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO4 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO7 ; 
 int /*<<< orphan*/  GPIO9 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_ctrl_clock (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  dib0700_set_gpio (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib8000_attach ; 
 int /*<<< orphan*/ * dib809x_dib8000_config ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 struct dvb_frontend* stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct dvb_frontend* stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,struct dvb_frontend*) ; 

__attribute__((used)) static int nim8096md_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_frontend *fe_slave;
	struct dib0700_adapter_state *state = adap->priv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		return -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(1000);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_clock(adap->dev, 72, 1);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_enumeration(&adap->dev->i2c_adap, 2, 18, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80, &dib809x_dib8000_config[0]);
	if (adap->fe_adap[0].fe == NULL)
		return -ENODEV;

	/* Needed to increment refcount */
	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		return -ENODEV;

	fe_slave = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82, &dib809x_dib8000_config[1]);
	state->dib8000_ops.set_slave_frontend(adap->fe_adap[0].fe, fe_slave);

	return fe_slave == NULL ?  -ENODEV : 0;
}