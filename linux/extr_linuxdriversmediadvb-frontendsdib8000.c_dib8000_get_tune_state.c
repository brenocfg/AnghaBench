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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int tune_state; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */

__attribute__((used)) static enum frontend_tune_state dib8000_get_tune_state(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;
	return state->tune_state;
}