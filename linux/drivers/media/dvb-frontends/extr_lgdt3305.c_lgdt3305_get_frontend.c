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
struct lgdt3305_state {int /*<<< orphan*/  current_frequency; int /*<<< orphan*/  current_modulation; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  frequency; int /*<<< orphan*/  modulation; } ;

/* Variables and functions */
 int /*<<< orphan*/  lg_dbg (char*) ; 

__attribute__((used)) static int lgdt3305_get_frontend(struct dvb_frontend *fe,
				 struct dtv_frontend_properties *p)
{
	struct lgdt3305_state *state = fe->demodulator_priv;

	lg_dbg("\n");

	p->modulation = state->current_modulation;
	p->frequency = state->current_frequency;
	return 0;
}