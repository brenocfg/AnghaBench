#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct dib7000m_state {TYPE_2__* current_agc; } ;
struct TYPE_3__ {scalar_t__ max; scalar_t__ min_thres; scalar_t__ min; scalar_t__ max_thres; } ;
struct TYPE_4__ {TYPE_1__ split; int /*<<< orphan*/  perform_agc_softsplit; } ;

/* Variables and functions */
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int dib7000m_write_word (struct dib7000m_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 

__attribute__((used)) static int dib7000m_agc_soft_split(struct dib7000m_state *state)
{
	u16 agc,split_offset;

	if(!state->current_agc || !state->current_agc->perform_agc_softsplit || state->current_agc->split.max == 0)
		return 0;

	// n_agc_global
	agc = dib7000m_read_word(state, 390);

	if (agc > state->current_agc->split.min_thres)
		split_offset = state->current_agc->split.min;
	else if (agc < state->current_agc->split.max_thres)
		split_offset = state->current_agc->split.max;
	else
		split_offset = state->current_agc->split.max *
			(agc - state->current_agc->split.min_thres) /
			(state->current_agc->split.max_thres - state->current_agc->split.min_thres);

	dprintk("AGC split_offset: %d\n", split_offset);

	// P_agc_force_split and P_agc_split_offset
	return dib7000m_write_word(state, 103, (dib7000m_read_word(state, 103) & 0xff00) | split_offset);
}