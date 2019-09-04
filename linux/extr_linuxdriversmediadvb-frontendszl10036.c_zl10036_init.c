#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zl10036_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct zl10036_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int zl10036_init_regs (struct zl10036_state*) ; 
 int zl10036_read_status_reg (struct zl10036_state*) ; 

__attribute__((used)) static int zl10036_init(struct dvb_frontend *fe)
{
	struct zl10036_state *state = fe->tuner_priv;
	int ret = 0;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	ret = zl10036_read_status_reg(state);
	if (ret < 0)
		return ret;

	/* Only init if Power-on-Reset bit is set? */
	ret = zl10036_init_regs(state);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	return ret;
}