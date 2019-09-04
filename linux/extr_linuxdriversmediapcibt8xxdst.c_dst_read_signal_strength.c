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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {int /*<<< orphan*/  decode_strength; } ;

/* Variables and functions */
 int dst_get_signal (struct dst_state*) ; 

__attribute__((used)) static int dst_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct dst_state *state = fe->demodulator_priv;

	int retval = dst_get_signal(state);
	*strength = state->decode_strength;

	return retval;
}