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
struct stv090x_state {scalar_t__ num_used; struct stv090x_state* internal; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  kfree (struct stv090x_state*) ; 
 int /*<<< orphan*/  remove_dev (struct stv090x_state*) ; 

__attribute__((used)) static void stv090x_release(struct dvb_frontend *fe)
{
	struct stv090x_state *state = fe->demodulator_priv;

	state->internal->num_used--;
	if (state->internal->num_used <= 0) {

		dprintk(FE_ERROR, 1, "Actually removing");

		remove_dev(state->internal);
		kfree(state->internal);
	}

	kfree(state);
}