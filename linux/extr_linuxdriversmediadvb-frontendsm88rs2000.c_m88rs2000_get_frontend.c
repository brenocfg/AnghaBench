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
struct m88rs2000_state {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  tuner_frequency; int /*<<< orphan*/  fec_inner; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  frequency; int /*<<< orphan*/  fec_inner; } ;

/* Variables and functions */

__attribute__((used)) static int m88rs2000_get_frontend(struct dvb_frontend *fe,
				  struct dtv_frontend_properties *c)
{
	struct m88rs2000_state *state = fe->demodulator_priv;

	c->fec_inner = state->fec_inner;
	c->frequency = state->tuner_frequency;
	c->symbol_rate = state->symbol_rate;
	return 0;
}