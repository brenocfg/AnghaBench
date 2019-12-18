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
typedef  int u8 ;
typedef  int u16 ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {struct dib7000m_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* agc_control ) (int /*<<< orphan*/ *,int) ;} ;
struct dib7000m_state {int agc_state; int /*<<< orphan*/  demod; TYPE_2__ cfg; TYPE_1__* current_agc; } ;
struct TYPE_3__ {int wbd_alpha; int /*<<< orphan*/  perform_agc_softsplit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_OF_FREQUENCY (int) ; 
 int /*<<< orphan*/  DIB7000M_POWER_INTERF_ANALOG_AGC ; 
 int /*<<< orphan*/  DIBX000_ADC_ON ; 
 int /*<<< orphan*/  dib7000m_agc_soft_split (struct dib7000m_state*) ; 
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int /*<<< orphan*/  dib7000m_restart_agc (struct dib7000m_state*) ; 
 int /*<<< orphan*/  dib7000m_set_adc_state (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_set_agc_config (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_set_power_mode (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_update_lna (struct dib7000m_state*) ; 
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dib7000m_agc_startup(struct dvb_frontend *demod)
{
	struct dtv_frontend_properties *ch = &demod->dtv_property_cache;
	struct dib7000m_state *state = demod->demodulator_priv;
	u16 cfg_72 = dib7000m_read_word(state, 72);
	int ret = -1;
	u8 *agc_state = &state->agc_state;
	u8 agc_split;

	switch (state->agc_state) {
		case 0:
			// set power-up level: interf+analog+AGC
			dib7000m_set_power_mode(state, DIB7000M_POWER_INTERF_ANALOG_AGC);
			dib7000m_set_adc_state(state, DIBX000_ADC_ON);

			if (dib7000m_set_agc_config(state, BAND_OF_FREQUENCY(ch->frequency/1000)) != 0)
				return -1;

			ret = 7; /* ADC power up */
			(*agc_state)++;
			break;

		case 1:
			/* AGC initialization */
			if (state->cfg.agc_control)
				state->cfg.agc_control(&state->demod, 1);

			dib7000m_write_word(state, 75, 32768);
			if (!state->current_agc->perform_agc_softsplit) {
				/* we are using the wbd - so slow AGC startup */
				dib7000m_write_word(state, 103, 1 << 8); /* force 0 split on WBD and restart AGC */
				(*agc_state)++;
				ret = 5;
			} else {
				/* default AGC startup */
				(*agc_state) = 4;
				/* wait AGC rough lock time */
				ret = 7;
			}

			dib7000m_restart_agc(state);
			break;

		case 2: /* fast split search path after 5sec */
			dib7000m_write_word(state,  72, cfg_72 | (1 << 4)); /* freeze AGC loop */
			dib7000m_write_word(state, 103, 2 << 9);            /* fast split search 0.25kHz */
			(*agc_state)++;
			ret = 14;
			break;

	case 3: /* split search ended */
			agc_split = (u8)dib7000m_read_word(state, 392); /* store the split value for the next time */
			dib7000m_write_word(state, 75, dib7000m_read_word(state, 390)); /* set AGC gain start value */

			dib7000m_write_word(state, 72,  cfg_72 & ~(1 << 4));   /* std AGC loop */
			dib7000m_write_word(state, 103, (state->current_agc->wbd_alpha << 9) | agc_split); /* standard split search */

			dib7000m_restart_agc(state);

			dprintk("SPLIT %p: %hd\n", demod, agc_split);

			(*agc_state)++;
			ret = 5;
			break;

		case 4: /* LNA startup */
			/* wait AGC accurate lock time */
			ret = 7;

			if (dib7000m_update_lna(state))
				// wait only AGC rough lock time
				ret = 5;
			else
				(*agc_state)++;
			break;

		case 5:
			dib7000m_agc_soft_split(state);

			if (state->cfg.agc_control)
				state->cfg.agc_control(&state->demod, 0);

			(*agc_state)++;
			break;

		default:
			break;
	}
	return ret;
}