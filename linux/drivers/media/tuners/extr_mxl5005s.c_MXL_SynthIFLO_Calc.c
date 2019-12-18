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
struct mxl5005s_state {int Mode; scalar_t__ IF_Mode; int Chan_Bandwidth; scalar_t__ IF_OUT; scalar_t__ IF_LO; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static void MXL_SynthIFLO_Calc(struct dvb_frontend *fe)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	if (state->Mode == 1) /* Digital Mode */
		state->IF_LO = state->IF_OUT;
	else /* Analog Mode */ {
		if (state->IF_Mode == 0) /* Analog Zero IF mode */
			state->IF_LO = state->IF_OUT + 400000;
		else /* Analog Low IF mode */
			state->IF_LO = state->IF_OUT + state->Chan_Bandwidth/2;
	}
}