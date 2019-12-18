#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dvb_frontend {struct drx39xxj_state* demodulator_priv; } ;
struct drx_demod_instance {int dummy; } ;
struct drx39xxj_state {int i2c_gate_open; struct drx_demod_instance* demod; } ;

/* Variables and functions */
 int ctrl_i2c_bridge (struct drx_demod_instance*,int*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int drx39xxj_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct drx39xxj_state *state = fe->demodulator_priv;
	struct drx_demod_instance *demod = state->demod;
	bool i2c_gate_state;
	int result;

#ifdef DJH_DEBUG
	pr_debug("i2c gate call: enable=%d state=%d\n", enable,
	       state->i2c_gate_open);
#endif

	if (enable)
		i2c_gate_state = true;
	else
		i2c_gate_state = false;

	if (state->i2c_gate_open == enable) {
		/* We're already in the desired state */
		return 0;
	}

	result = ctrl_i2c_bridge(demod, &i2c_gate_state);
	if (result != 0) {
		pr_err("drx39xxj: could not open i2c gate [%d]\n",
		       result);
		dump_stack();
	} else {
		state->i2c_gate_open = enable;
	}
	return 0;
}