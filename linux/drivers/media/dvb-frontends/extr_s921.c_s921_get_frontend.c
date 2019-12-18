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
struct s921_state {int /*<<< orphan*/  currentfreq; } ;
struct dvb_frontend {struct s921_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  delivery_system; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_ISDBT ; 

__attribute__((used)) static int s921_get_frontend(struct dvb_frontend *fe,
			     struct dtv_frontend_properties *p)
{
	struct s921_state *state = fe->demodulator_priv;

	/* FIXME: Probably it is possible to get it from regs f1 and f2 */
	p->frequency = state->currentfreq;
	p->delivery_system = SYS_ISDBT;

	return 0;
}