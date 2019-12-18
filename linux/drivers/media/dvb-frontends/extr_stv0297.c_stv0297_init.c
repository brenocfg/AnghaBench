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
struct stv0297_state {scalar_t__ last_ber; TYPE_1__* config; } ;
struct dvb_frontend {struct stv0297_state* demodulator_priv; } ;
struct TYPE_2__ {int* inittab; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,int) ; 

__attribute__((used)) static int stv0297_init(struct dvb_frontend *fe)
{
	struct stv0297_state *state = fe->demodulator_priv;
	int i;

	/* load init table */
	for (i=0; !(state->config->inittab[i] == 0xff && state->config->inittab[i+1] == 0xff); i+=2)
		stv0297_writereg(state, state->config->inittab[i], state->config->inittab[i+1]);
	msleep(200);

	state->last_ber = 0;

	return 0;
}