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
struct dvb_frontend {struct cx24120_state* demodulator_priv; } ;
struct cx24120_state {int fe_status; scalar_t__ need_clock_set; int /*<<< orphan*/  mpeg_enabled; TYPE_1__* i2c; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CX24120_HAS_CARRIER ; 
 int CX24120_HAS_LOCK ; 
 int CX24120_HAS_SIGNAL ; 
 int CX24120_HAS_VITERBI ; 
 int /*<<< orphan*/  CX24120_REG_STATUS ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  cx24120_get_stats (struct cx24120_state*) ; 
 int /*<<< orphan*/  cx24120_msg_mpeg_output_global_config (struct cx24120_state*,int) ; 
 int cx24120_readreg (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx24120_set_clock_ratios (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int cx24120_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct cx24120_state *state = fe->demodulator_priv;
	int lock;

	lock = cx24120_readreg(state, CX24120_REG_STATUS);

	dev_dbg(&state->i2c->dev, "status = 0x%02x\n", lock);

	*status = 0;

	if (lock & CX24120_HAS_SIGNAL)
		*status = FE_HAS_SIGNAL;
	if (lock & CX24120_HAS_CARRIER)
		*status |= FE_HAS_CARRIER;
	if (lock & CX24120_HAS_VITERBI)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
	if (lock & CX24120_HAS_LOCK)
		*status |= FE_HAS_LOCK;

	/*
	 * TODO: is FE_HAS_SYNC in the right place?
	 * Other cx241xx drivers have this slightly
	 * different
	 */

	state->fe_status = *status;
	cx24120_get_stats(state);

	/* Set the clock once tuned in */
	if (state->need_clock_set && *status & FE_HAS_LOCK) {
		/* Set clock ratios */
		cx24120_set_clock_ratios(fe);

		/* Old driver would do a msleep(200) here */

		/* Renable mpeg output */
		if (!state->mpeg_enabled)
			cx24120_msg_mpeg_output_global_config(state, 1);

		state->need_clock_set = 0;
	}

	return 0;
}