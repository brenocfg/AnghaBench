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
struct TYPE_6__ {int /*<<< orphan*/ * (* init ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* i2c_enumeration ) (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ;} ;
struct dib0700_adapter_state {TYPE_2__ dib8000_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fe; } ;

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
 int /*<<< orphan*/ * dib807x_dib8000_config ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stk807xpvr_frontend_attach0(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *state = adap->priv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		return -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(500);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_clock(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	/* initialize IC 0 */
	state->dib8000_ops.i2c_enumeration(&adap->dev->i2c_adap, 1, 0x22, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	return adap->fe_adap[0].fe == NULL ? -ENODEV : 0;
}