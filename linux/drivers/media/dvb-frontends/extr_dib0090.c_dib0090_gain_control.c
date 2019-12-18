#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct TYPE_9__ {scalar_t__ p1g; } ;
struct dib0090_state {int tune_state; scalar_t__ current_band; int rf_gain_limit; int* rf_ramp; int current_gain; int* bb_ramp; scalar_t__ wbd_target; int rf_lt_def; scalar_t__ agc_freeze; TYPE_3__* fe; scalar_t__ agc_step; TYPE_5__* config; TYPE_4__ identity; int /*<<< orphan*/  current_rf; } ;
typedef  int s32 ;
typedef  scalar_t__ s16 ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;
struct TYPE_10__ {int (* get_adc_power ) (struct dvb_frontend*) ;} ;
struct TYPE_7__ {scalar_t__ delivery_system; scalar_t__ modulation; TYPE_1__* layer; } ;
struct TYPE_8__ {TYPE_2__ dtv_property_cache; } ;
struct TYPE_6__ {scalar_t__ segment_count; scalar_t__ modulation; } ;

/* Variables and functions */
 scalar_t__ ADC_TARGET ; 
 scalar_t__ BAND_CBAND ; 
 scalar_t__ BAND_SBAND ; 
 scalar_t__ BAND_VHF ; 
 int CT_AGC_START ; 
 int CT_AGC_STEP_0 ; 
 int CT_AGC_STEP_1 ; 
 int CT_AGC_STOP ; 
 int GAIN_ALPHA ; 
 scalar_t__ QAM_16 ; 
 scalar_t__ QAM_64 ; 
 scalar_t__ STANDARD_DAB ; 
 scalar_t__ STANDARD_DVBT ; 
 scalar_t__ SYS_ISDBT ; 
 int WBD_ALPHA ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  bb_ramp_boost ; 
 int /*<<< orphan*/  bb_ramp_pwm_normal ; 
 int /*<<< orphan*/  bb_ramp_pwm_normal_socs ; 
 int /*<<< orphan*/  dib0090_gain_apply (struct dib0090_state*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ dib0090_get_slow_adc_val (struct dib0090_state*) ; 
 int /*<<< orphan*/  dib0090_set_bbramp (struct dib0090_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib0090_set_rframp (struct dib0090_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib0090_wbd_target (struct dib0090_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ dib0090_wbd_to_db (struct dib0090_state*,scalar_t__) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  rf_ramp_pwm_cband ; 
 int /*<<< orphan*/  rf_ramp_pwm_cband_7090p ; 
 int /*<<< orphan*/  rf_ramp_pwm_uhf ; 
 int /*<<< orphan*/  rf_ramp_pwm_vhf ; 
 int /*<<< orphan*/  rf_ramp_sband ; 
 int stub1 (struct dvb_frontend*) ; 

int dib0090_gain_control(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	enum frontend_tune_state *tune_state = &state->tune_state;
	int ret = 10;

	u16 wbd_val = 0;
	u8 apply_gain_immediatly = 1;
	s16 wbd_error = 0, adc_error = 0;

	if (*tune_state == CT_AGC_START) {
		state->agc_freeze = 0;
		dib0090_write_reg(state, 0x04, 0x0);

#ifdef CONFIG_BAND_SBAND
		if (state->current_band == BAND_SBAND) {
			dib0090_set_rframp(state, rf_ramp_sband);
			dib0090_set_bbramp(state, bb_ramp_boost);
		} else
#endif
#ifdef CONFIG_BAND_VHF
		if (state->current_band == BAND_VHF && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_vhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		} else
#endif
#ifdef CONFIG_BAND_CBAND
		if (state->current_band == BAND_CBAND && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_cband);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		} else
#endif
		if ((state->current_band == BAND_CBAND || state->current_band == BAND_VHF) && state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_cband_7090p);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal_socs);
		} else {
			dib0090_set_rframp(state, rf_ramp_pwm_uhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		}

		dib0090_write_reg(state, 0x32, 0);
		dib0090_write_reg(state, 0x39, 0);

		dib0090_wbd_target(state, state->current_rf);

		state->rf_gain_limit = state->rf_ramp[0] << WBD_ALPHA;
		state->current_gain = ((state->rf_ramp[0] + state->bb_ramp[0]) / 2) << GAIN_ALPHA;

		*tune_state = CT_AGC_STEP_0;
	} else if (!state->agc_freeze) {
		s16 wbd = 0, i, cnt;

		int adc;
		wbd_val = dib0090_get_slow_adc_val(state);

		if (*tune_state == CT_AGC_STEP_0)
			cnt = 5;
		else
			cnt = 1;

		for (i = 0; i < cnt; i++) {
			wbd_val = dib0090_get_slow_adc_val(state);
			wbd += dib0090_wbd_to_db(state, wbd_val);
		}
		wbd /= cnt;
		wbd_error = state->wbd_target - wbd;

		if (*tune_state == CT_AGC_STEP_0) {
			if (wbd_error < 0 && state->rf_gain_limit > 0 && !state->identity.p1g) {
#ifdef CONFIG_BAND_CBAND
				/* in case of CBAND tune reduce first the lt_gain2 before adjusting the RF gain */
				u8 ltg2 = (state->rf_lt_def >> 10) & 0x7;
				if (state->current_band == BAND_CBAND && ltg2) {
					ltg2 >>= 1;
					state->rf_lt_def &= ltg2 << 10;	/* reduce in 3 steps from 7 to 0 */
				}
#endif
			} else {
				state->agc_step = 0;
				*tune_state = CT_AGC_STEP_1;
			}
		} else {
			/* calc the adc power */
			adc = state->config->get_adc_power(fe);
			adc = (adc * ((s32) 355774) + (((s32) 1) << 20)) >> 21;	/* included in [0:-700] */

			adc_error = (s16) (((s32) ADC_TARGET) - adc);
#ifdef CONFIG_STANDARD_DAB
			if (state->fe->dtv_property_cache.delivery_system == STANDARD_DAB)
				adc_error -= 10;
#endif
#ifdef CONFIG_STANDARD_DVBT
			if (state->fe->dtv_property_cache.delivery_system == STANDARD_DVBT &&
					(state->fe->dtv_property_cache.modulation == QAM_64 || state->fe->dtv_property_cache.modulation == QAM_16))
				adc_error += 60;
#endif
#ifdef CONFIG_SYS_ISDBT
			if ((state->fe->dtv_property_cache.delivery_system == SYS_ISDBT) && (((state->fe->dtv_property_cache.layer[0].segment_count >
								0)
							&&
							((state->fe->dtv_property_cache.layer[0].modulation ==
							  QAM_64)
							 || (state->fe->dtv_property_cache.
								 layer[0].modulation == QAM_16)))
						||
						((state->fe->dtv_property_cache.layer[1].segment_count >
						  0)
						 &&
						 ((state->fe->dtv_property_cache.layer[1].modulation ==
						   QAM_64)
						  || (state->fe->dtv_property_cache.
							  layer[1].modulation == QAM_16)))
						||
						((state->fe->dtv_property_cache.layer[2].segment_count >
						  0)
						 &&
						 ((state->fe->dtv_property_cache.layer[2].modulation ==
						   QAM_64)
						  || (state->fe->dtv_property_cache.
							  layer[2].modulation == QAM_16)))
						)
				)
				adc_error += 60;
#endif

			if (*tune_state == CT_AGC_STEP_1) {	/* quickly go to the correct range of the ADC power */
				if (abs(adc_error) < 50 || state->agc_step++ > 5) {

#ifdef CONFIG_STANDARD_DAB
					if (state->fe->dtv_property_cache.delivery_system == STANDARD_DAB) {
						dib0090_write_reg(state, 0x02, (1 << 15) | (15 << 11) | (31 << 6) | (63));	/* cap value = 63 : narrow BB filter : Fc = 1.8MHz */
						dib0090_write_reg(state, 0x04, 0x0);
					} else
#endif
					{
						dib0090_write_reg(state, 0x02, (1 << 15) | (3 << 11) | (6 << 6) | (32));
						dib0090_write_reg(state, 0x04, 0x01);	/*0 = 1KHz ; 1 = 150Hz ; 2 = 50Hz ; 3 = 50KHz ; 4 = servo fast */
					}

					*tune_state = CT_AGC_STOP;
				}
			} else {
				/* everything higher than or equal to CT_AGC_STOP means tracking */
				ret = 100;	/* 10ms interval */
				apply_gain_immediatly = 0;
			}
		}
#ifdef DEBUG_AGC
		dprintk
			("tune state %d, ADC = %3ddB (ADC err %3d) WBD %3ddB (WBD err %3d, WBD val SADC: %4d), RFGainLimit (TOP): %3d, signal: %3ddBm",
			 (u32) *tune_state, (u32) adc, (u32) adc_error, (u32) wbd, (u32) wbd_error, (u32) wbd_val,
			 (u32) state->rf_gain_limit >> WBD_ALPHA, (s32) 200 + adc - (state->current_gain >> GAIN_ALPHA));
#endif
	}

	/* apply gain */
	if (!state->agc_freeze)
		dib0090_gain_apply(state, adc_error, wbd_error, apply_gain_immediatly);
	return ret;
}