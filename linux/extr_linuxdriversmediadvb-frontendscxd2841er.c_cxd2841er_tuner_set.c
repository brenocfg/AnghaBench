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
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct cxd2841er_priv* demodulator_priv; } ;
struct cxd2841er_priv {int flags; } ;

/* Variables and functions */
 int CXD2841ER_USE_GATECTRL ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int cxd2841er_tuner_set(struct dvb_frontend *fe)
{
	struct cxd2841er_priv *priv = fe->demodulator_priv;

	if ((priv->flags & CXD2841ER_USE_GATECTRL) && fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	if ((priv->flags & CXD2841ER_USE_GATECTRL) && fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return 0;
}