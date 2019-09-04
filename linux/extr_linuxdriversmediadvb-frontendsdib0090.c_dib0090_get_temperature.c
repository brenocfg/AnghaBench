#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dib0090_state {int wbdmux; int bias; int adc_diff; TYPE_1__* config; int /*<<< orphan*/  calibrate; int /*<<< orphan*/  temperature; } ;
typedef  int s16 ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;
struct TYPE_2__ {int /*<<< orphan*/  analog_output; } ;

/* Variables and functions */
#define  CT_TUNER_START 131 
#define  CT_TUNER_STEP_0 130 
#define  CT_TUNER_STEP_1 129 
#define  CT_TUNER_STEP_2 128 
 int /*<<< orphan*/  TEMP_CAL ; 
 void* dib0090_get_slow_adc_val (struct dib0090_state*) ; 
 int dib0090_read_reg (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib0090_get_temperature(struct dib0090_state *state, enum frontend_tune_state *tune_state)
{
	int ret = 15;
	s16 val;

	switch (*tune_state) {
	case CT_TUNER_START:
		state->wbdmux = dib0090_read_reg(state, 0x10);
		dib0090_write_reg(state, 0x10, (state->wbdmux & ~(0xff << 3)) | (0x8 << 3));

		state->bias = dib0090_read_reg(state, 0x13);
		dib0090_write_reg(state, 0x13, state->bias | (0x3 << 8));

		*tune_state = CT_TUNER_STEP_0;
		/* wait for the WBDMUX to switch and for the ADC to sample */
		break;

	case CT_TUNER_STEP_0:
		state->adc_diff = dib0090_get_slow_adc_val(state);
		dib0090_write_reg(state, 0x13, (state->bias & ~(0x3 << 8)) | (0x2 << 8));
		*tune_state = CT_TUNER_STEP_1;
		break;

	case CT_TUNER_STEP_1:
		val = dib0090_get_slow_adc_val(state);
		state->temperature = ((s16) ((val - state->adc_diff) * 180) >> 8) + 55;

		dprintk("temperature: %d C\n", state->temperature - 30);

		*tune_state = CT_TUNER_STEP_2;
		break;

	case CT_TUNER_STEP_2:
		dib0090_write_reg(state, 0x13, state->bias);
		dib0090_write_reg(state, 0x10, state->wbdmux);	/* write back original WBDMUX */

		*tune_state = CT_TUNER_START;
		state->calibrate &= ~TEMP_CAL;
		if (state->config->analog_output == 0)
			dib0090_write_reg(state, 0x23, dib0090_read_reg(state, 0x23) | (1 << 14));

		break;

	default:
		ret = 0;
		break;
	}
	return ret;
}