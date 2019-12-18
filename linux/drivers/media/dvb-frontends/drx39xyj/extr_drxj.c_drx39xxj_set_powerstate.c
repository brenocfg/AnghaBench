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
struct drx39xxj_state {struct drx_demod_instance* demod; } ;
typedef  enum drx_power_mode { ____Placeholder_drx_power_mode } drx_power_mode ;

/* Variables and functions */
 int DRX_POWER_DOWN ; 
 int DRX_POWER_UP ; 
 int ctrl_power_mode (struct drx_demod_instance*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int drx39xxj_set_powerstate(struct dvb_frontend *fe, int enable)
{
	struct drx39xxj_state *state = fe->demodulator_priv;
	struct drx_demod_instance *demod = state->demod;
	int result;
	enum drx_power_mode power_mode;

	if (enable)
		power_mode = DRX_POWER_UP;
	else
		power_mode = DRX_POWER_DOWN;

	result = ctrl_power_mode(demod, &power_mode);
	if (result != 0) {
		pr_err("Power state change failed\n");
		return 0;
	}

	return 0;
}