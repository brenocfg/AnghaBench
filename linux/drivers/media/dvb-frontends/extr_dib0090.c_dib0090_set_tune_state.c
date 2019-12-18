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
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {int tune_state; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */

int dib0090_set_tune_state(struct dvb_frontend *fe, enum frontend_tune_state tune_state)
{
	struct dib0090_state *state = fe->tuner_priv;

	state->tune_state = tune_state;
	return 0;
}