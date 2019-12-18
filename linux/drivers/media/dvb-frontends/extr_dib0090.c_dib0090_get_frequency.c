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
typedef  int u32 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {int current_rf; } ;

/* Variables and functions */

__attribute__((used)) static int dib0090_get_frequency(struct dvb_frontend *fe, u32 * frequency)
{
	struct dib0090_state *state = fe->tuner_priv;

	*frequency = 1000 * state->current_rf;
	return 0;
}