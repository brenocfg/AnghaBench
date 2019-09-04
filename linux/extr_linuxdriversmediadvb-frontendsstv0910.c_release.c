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
struct stv {scalar_t__ count; struct stv* base; int /*<<< orphan*/  stvlist; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct stv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release(struct dvb_frontend *fe)
{
	struct stv *state = fe->demodulator_priv;

	state->base->count--;
	if (state->base->count == 0) {
		list_del(&state->base->stvlist);
		kfree(state->base);
	}
	kfree(state);
}