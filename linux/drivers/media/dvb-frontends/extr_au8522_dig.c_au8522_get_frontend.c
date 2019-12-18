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
struct dvb_frontend {struct au8522_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  modulation; int /*<<< orphan*/  frequency; } ;
struct au8522_state {int /*<<< orphan*/  current_modulation; int /*<<< orphan*/  current_frequency; } ;

/* Variables and functions */

__attribute__((used)) static int au8522_get_frontend(struct dvb_frontend *fe,
			       struct dtv_frontend_properties *c)
{
	struct au8522_state *state = fe->demodulator_priv;

	c->frequency = state->current_frequency;
	c->modulation = state->current_modulation;

	return 0;
}