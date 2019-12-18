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
typedef  int /*<<< orphan*/  u32 ;
struct tda_state {int /*<<< orphan*/  IF; } ;
struct dvb_frontend {struct tda_state* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static int get_if_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct tda_state *state = fe->tuner_priv;

	*frequency = state->IF;
	return 0;
}