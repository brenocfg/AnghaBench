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
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {struct dvb_frontend** fe; } ;

/* Variables and functions */
 int MAX_NUMBER_OF_FRONTENDS ; 

struct dvb_frontend *dib9000_get_slave_frontend(struct dvb_frontend *fe, int slave_index)
{
	struct dib9000_state *state = fe->demodulator_priv;

	if (slave_index >= MAX_NUMBER_OF_FRONTENDS)
		return NULL;
	return state->fe[slave_index];
}