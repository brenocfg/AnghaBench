#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * adap; } ;
struct tuner_simple_priv {TYPE_2__* tun; TYPE_3__ i2c_props; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct tuner_simple_priv* tuner_priv; } ;
struct TYPE_5__ {int* initdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int tuner_i2c_xfer_send (TYPE_3__*,int*,int) ; 

__attribute__((used)) static int simple_init(struct dvb_frontend *fe)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;

	if (priv->i2c_props.adap == NULL)
		return -EINVAL;

	if (priv->tun->initdata) {
		int ret;

		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = tuner_i2c_xfer_send(&priv->i2c_props,
					  priv->tun->initdata + 1,
					  priv->tun->initdata[0]);
		if (ret != priv->tun->initdata[0])
			return ret;
	}

	return 0;
}