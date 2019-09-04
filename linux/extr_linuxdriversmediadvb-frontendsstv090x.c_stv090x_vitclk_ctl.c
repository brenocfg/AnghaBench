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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {int demod; TYPE_1__* internal; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  STOP_CLKVIT1_FIELD ; 
 int /*<<< orphan*/  STOP_CLKVIT2_FIELD ; 
#define  STV090x_DEMODULATOR_0 129 
#define  STV090x_DEMODULATOR_1 128 
 int /*<<< orphan*/  STV090x_SETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STV090x_STOPCLK2 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stv090x_read_reg (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_write_reg (struct stv090x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv090x_vitclk_ctl(struct stv090x_state *state, int enable)
{
	u32 reg;

	switch (state->demod) {
	case STV090x_DEMODULATOR_0:
		mutex_lock(&state->internal->demod_lock);
		reg = stv090x_read_reg(state, STV090x_STOPCLK2);
		STV090x_SETFIELD(reg, STOP_CLKVIT1_FIELD, enable);
		if (stv090x_write_reg(state, STV090x_STOPCLK2, reg) < 0)
			goto err;
		mutex_unlock(&state->internal->demod_lock);
		break;

	case STV090x_DEMODULATOR_1:
		mutex_lock(&state->internal->demod_lock);
		reg = stv090x_read_reg(state, STV090x_STOPCLK2);
		STV090x_SETFIELD(reg, STOP_CLKVIT2_FIELD, enable);
		if (stv090x_write_reg(state, STV090x_STOPCLK2, reg) < 0)
			goto err;
		mutex_unlock(&state->internal->demod_lock);
		break;

	default:
		dprintk(FE_ERROR, 1, "Wrong demodulator!");
		break;
	}
	return 0;
err:
	mutex_unlock(&state->internal->demod_lock);
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}