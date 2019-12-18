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
typedef  int u16 ;
struct dvb_frontend {struct as102_state* demodulator_priv; } ;
struct as102_state {int signal_strength; } ;

/* Variables and functions */

__attribute__((used)) static int as102_fe_read_signal_strength(struct dvb_frontend *fe,
					 u16 *strength)
{
	struct as102_state *state = fe->demodulator_priv;

	*strength = (((0xffff * 400) * state->signal_strength + 41000) * 2);

	return 0;
}