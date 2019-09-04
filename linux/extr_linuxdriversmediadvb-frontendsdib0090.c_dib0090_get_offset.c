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
struct dib0090_state {int /*<<< orphan*/  adc_diff; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */
#define  CT_TUNER_STEP_2 130 
#define  CT_TUNER_STEP_3 129 
#define  CT_TUNER_STEP_4 128 
 int CT_TUNER_STEP_5 ; 
 int INTERN_WAIT ; 
 int /*<<< orphan*/  dib0090_read_reg (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 

__attribute__((used)) static int dib0090_get_offset(struct dib0090_state *state, enum frontend_tune_state *tune_state)
{
	int ret = INTERN_WAIT * 10;

	switch (*tune_state) {
	case CT_TUNER_STEP_2:
		/* Turns to positive */
		dib0090_write_reg(state, 0x1f, 0x7);
		*tune_state = CT_TUNER_STEP_3;
		break;

	case CT_TUNER_STEP_3:
		state->adc_diff = dib0090_read_reg(state, 0x1d);

		/* Turns to negative */
		dib0090_write_reg(state, 0x1f, 0x4);
		*tune_state = CT_TUNER_STEP_4;
		break;

	case CT_TUNER_STEP_4:
		state->adc_diff -= dib0090_read_reg(state, 0x1d);
		*tune_state = CT_TUNER_STEP_5;
		ret = 0;
		break;

	default:
		break;
	}

	return ret;
}