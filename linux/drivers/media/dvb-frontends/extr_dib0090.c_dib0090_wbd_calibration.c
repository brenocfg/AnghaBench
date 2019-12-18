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
typedef  int u8 ;
struct dib0090_wbd_slope {int max_freq; int wbd_gain; } ;
struct dib0090_state {int current_rf; int wbd_calibration_gain; int /*<<< orphan*/  calibrate; int /*<<< orphan*/  wbd_offset; int /*<<< orphan*/  current_band; struct dib0090_wbd_slope* current_wbd_table; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_LBAND ; 
 int /*<<< orphan*/  BAND_SBAND ; 
#define  CT_TUNER_START 129 
#define  CT_TUNER_STEP_0 128 
 int EN_UHF ; 
 int /*<<< orphan*/  WBD_CAL ; 
 int /*<<< orphan*/  dib0090_get_slow_adc_val (struct dib0090_state*) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib0090_wbd_calibration(struct dib0090_state *state, enum frontend_tune_state *tune_state)
{
	u8 wbd_gain;
	const struct dib0090_wbd_slope *wbd = state->current_wbd_table;

	switch (*tune_state) {
	case CT_TUNER_START:
		while (state->current_rf / 1000 > wbd->max_freq)
			wbd++;
		if (wbd->wbd_gain != 0)
			wbd_gain = wbd->wbd_gain;
		else {
			wbd_gain = 4;
#if defined(CONFIG_BAND_LBAND) || defined(CONFIG_BAND_SBAND)
			if ((state->current_band == BAND_LBAND) || (state->current_band == BAND_SBAND))
				wbd_gain = 2;
#endif
		}

		if (wbd_gain == state->wbd_calibration_gain) {	/* the WBD calibration has already been done */
			*tune_state = CT_TUNER_START;
			state->calibrate &= ~WBD_CAL;
			return 0;
		}

		dib0090_write_reg(state, 0x10, 0x1b81 | (1 << 10) | (wbd_gain << 13) | (1 << 3));

		dib0090_write_reg(state, 0x24, ((EN_UHF & 0x0fff) | (1 << 1)));
		*tune_state = CT_TUNER_STEP_0;
		state->wbd_calibration_gain = wbd_gain;
		return 90;	/* wait for the WBDMUX to switch and for the ADC to sample */

	case CT_TUNER_STEP_0:
		state->wbd_offset = dib0090_get_slow_adc_val(state);
		dprintk("WBD calibration offset = %d\n", state->wbd_offset);
		*tune_state = CT_TUNER_START;	/* reset done -> real tuning can now begin */
		state->calibrate &= ~WBD_CAL;
		break;

	default:
		break;
	}
	return 0;
}