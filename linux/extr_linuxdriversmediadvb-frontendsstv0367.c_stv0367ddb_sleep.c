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
struct stv0367_state {int activedemod; } ;
struct dvb_frontend {struct stv0367_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  demod_cab 129 
 void* demod_none ; 
#define  demod_ter 128 
 int stv0367cab_sleep (struct dvb_frontend*) ; 
 int stv0367ter_sleep (struct dvb_frontend*) ; 

__attribute__((used)) static int stv0367ddb_sleep(struct dvb_frontend *fe)
{
	struct stv0367_state *state = fe->demodulator_priv;

	switch (state->activedemod) {
	case demod_ter:
		state->activedemod = demod_none;
		return stv0367ter_sleep(fe);
	case demod_cab:
		state->activedemod = demod_none;
		return stv0367cab_sleep(fe);
	default:
		break;
	}

	return -EINVAL;
}