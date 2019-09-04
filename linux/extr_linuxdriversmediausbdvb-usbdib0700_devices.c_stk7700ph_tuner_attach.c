#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {TYPE_2__* fe_adap; struct dib0700_adapter_state* priv; } ;
struct TYPE_7__ {struct i2c_adapter* (* get_i2c_master ) (TYPE_3__*,int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {TYPE_1__ dib7000p_ops; } ;
struct TYPE_10__ {struct i2c_adapter* i2c_adap; } ;
struct TYPE_9__ {int /*<<< orphan*/  callback; } ;
struct TYPE_8__ {TYPE_3__* fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int ENODEV ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stk7700ph_xc3028_callback ; 
 TYPE_4__ stk7700ph_xc3028_config ; 
 struct i2c_adapter* stub1 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xc2028_attach ; 

__attribute__((used)) static int stk7700ph_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct i2c_adapter *tun_i2c;
	struct dib0700_adapter_state *state = adap->priv;

	tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
		DIBX000_I2C_INTERFACE_TUNER, 1);

	stk7700ph_xc3028_config.i2c_adap = tun_i2c;

	/* FIXME: generalize & move to common area */
	adap->fe_adap[0].fe->callback = stk7700ph_xc3028_callback;

	return dvb_attach(xc2028_attach, adap->fe_adap[0].fe, &stk7700ph_xc3028_config)
		== NULL ? -ENODEV : 0;
}