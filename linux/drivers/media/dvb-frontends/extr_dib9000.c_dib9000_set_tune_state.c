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
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {int tune_state; int /*<<< orphan*/  status; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */
 int CT_DEMOD_START ; 
 int /*<<< orphan*/  FE_STATUS_TUNE_PENDING ; 

__attribute__((used)) static int dib9000_set_tune_state(struct dvb_frontend *fe, enum frontend_tune_state tune_state)
{
	struct dib9000_state *state = fe->demodulator_priv;
	state->tune_state = tune_state;
	if (tune_state == CT_DEMOD_START)
		state->status = FE_STATUS_TUNE_PENDING;

	return 0;
}