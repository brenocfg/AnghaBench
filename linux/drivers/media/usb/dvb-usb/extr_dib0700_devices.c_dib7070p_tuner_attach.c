#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {scalar_t__ id; TYPE_4__* fe_adap; struct dib0700_adapter_state* priv; } ;
struct TYPE_7__ {struct i2c_adapter* (* get_i2c_master ) (TYPE_5__*,int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {int /*<<< orphan*/  set_param_save; TYPE_1__ dib7000p_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_9__ {TYPE_2__ tuner_ops; } ;
struct TYPE_11__ {TYPE_3__ ops; } ;
struct TYPE_10__ {TYPE_5__* fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int ENODEV ; 
 int /*<<< orphan*/  dib0070_attach ; 
 int /*<<< orphan*/  dib7070_set_param_override ; 
 int /*<<< orphan*/ * dib7070p_dib0070_config ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_5__*,struct i2c_adapter*,int /*<<< orphan*/ *) ; 
 struct i2c_adapter* stub1 (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib7070p_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *st = adap->priv;
	struct i2c_adapter *tun_i2c = st->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_TUNER, 1);

	if (adap->id == 0) {
		if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c, &dib7070p_dib0070_config[0]) == NULL)
			return -ENODEV;
	} else {
		if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c, &dib7070p_dib0070_config[1]) == NULL)
			return -ENODEV;
	}

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7070_set_param_override;
	return 0;
}