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
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {int* gain; int rf_gain_limit; int rf_lt_def; } ;

/* Variables and functions */

void dib0090_get_current_gain(struct dvb_frontend *fe, u16 * rf, u16 * bb, u16 * rf_gain_limit, u16 * rflt)
{
	struct dib0090_state *state = fe->tuner_priv;
	if (rf)
		*rf = state->gain[0];
	if (bb)
		*bb = state->gain[1];
	if (rf_gain_limit)
		*rf_gain_limit = state->rf_gain_limit;
	if (rflt)
		*rflt = (state->rf_lt_def >> 10) & 0x7;
}