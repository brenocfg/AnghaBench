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
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {size_t id; TYPE_2__* fe_adap; struct dib0700_adapter_state* priv; } ;
struct TYPE_3__ {struct i2c_adapter* (* get_i2c_master ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {TYPE_1__ dib7000p_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int ENODEV ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt2266_attach ; 
 int /*<<< orphan*/ * stk7700d_mt2266_config ; 
 struct i2c_adapter* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk7700d_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct i2c_adapter *tun_i2c;
	struct dib0700_adapter_state *state = adap->priv;

	tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
					    DIBX000_I2C_INTERFACE_TUNER, 1);
	return dvb_attach(mt2266_attach, adap->fe_adap[0].fe, tun_i2c,
		&stk7700d_mt2266_config[adap->id]) == NULL ? -ENODEV : 0;
}