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
typedef  scalar_t__ u16 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct TYPE_4__ {int version; scalar_t__ in_soc; } ;
struct dib0090_state {scalar_t__ current_band; scalar_t__* rf_ramp; TYPE_2__ identity; TYPE_1__* config; } ;
struct TYPE_3__ {scalar_t__ is_dib7090e; scalar_t__ use_pwm_agc; } ;

/* Variables and functions */
 scalar_t__ BAND_CBAND ; 
 scalar_t__ BAND_UHF ; 
 scalar_t__ BAND_VHF ; 
 int P1D_E_F ; 
 int SOC_7090_P1G_11R1 ; 
 int SOC_7090_P1G_21R1 ; 
 int SOC_8090_P1G_11R1 ; 
 int SOC_8090_P1G_21R1 ; 
 scalar_t__* bb_ramp_pwm_normal ; 
 scalar_t__* bb_ramp_pwm_normal_socs ; 
 int /*<<< orphan*/  dib0090_set_bbramp_pwm (struct dib0090_state*,scalar_t__ const*) ; 
 int /*<<< orphan*/  dib0090_set_rframp_pwm (struct dib0090_state*,scalar_t__ const*) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__* rf_ramp_pwm_cband ; 
 scalar_t__* rf_ramp_pwm_cband_7090e_sensitivity ; 
 scalar_t__* rf_ramp_pwm_cband_7090p ; 
 scalar_t__* rf_ramp_pwm_cband_8090 ; 
 scalar_t__* rf_ramp_pwm_uhf ; 
 scalar_t__* rf_ramp_pwm_uhf_7090 ; 
 scalar_t__* rf_ramp_pwm_uhf_8090 ; 
 scalar_t__* rf_ramp_pwm_vhf ; 

void dib0090_pwm_gain_reset(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	const u16 *bb_ramp = bb_ramp_pwm_normal; /* default baseband config */
	const u16 *rf_ramp = NULL;
	u8 en_pwm_rf_mux = 1;

	/* reset the AGC */
	if (state->config->use_pwm_agc) {
		if (state->current_band == BAND_CBAND) {
			if (state->identity.in_soc) {
				bb_ramp = bb_ramp_pwm_normal_socs;
				if (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
					rf_ramp = rf_ramp_pwm_cband_8090;
				else if (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1) {
					if (state->config->is_dib7090e) {
						if (state->rf_ramp == NULL)
							rf_ramp = rf_ramp_pwm_cband_7090e_sensitivity;
						else
							rf_ramp = state->rf_ramp;
					} else
						rf_ramp = rf_ramp_pwm_cband_7090p;
				}
			} else
				rf_ramp = rf_ramp_pwm_cband;
		} else

			if (state->current_band == BAND_VHF) {
				if (state->identity.in_soc) {
					bb_ramp = bb_ramp_pwm_normal_socs;
					/* rf_ramp = &rf_ramp_pwm_vhf_socs; */ /* TODO */
				} else
					rf_ramp = rf_ramp_pwm_vhf;
			} else if (state->current_band == BAND_UHF) {
				if (state->identity.in_soc) {
					bb_ramp = bb_ramp_pwm_normal_socs;
					if (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
						rf_ramp = rf_ramp_pwm_uhf_8090;
					else if (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1)
						rf_ramp = rf_ramp_pwm_uhf_7090;
				} else
					rf_ramp = rf_ramp_pwm_uhf;
			}
		if (rf_ramp)
			dib0090_set_rframp_pwm(state, rf_ramp);
		dib0090_set_bbramp_pwm(state, bb_ramp);

		/* activate the ramp generator using PWM control */
		if (state->rf_ramp)
			dprintk("ramp RF gain = %d BAND = %s version = %d\n",
				state->rf_ramp[0],
				(state->current_band == BAND_CBAND) ? "CBAND" : "NOT CBAND",
				state->identity.version & 0x1f);

		if (rf_ramp && ((state->rf_ramp && state->rf_ramp[0] == 0) ||
		    (state->current_band == BAND_CBAND &&
		    (state->identity.version & 0x1f) <= P1D_E_F))) {
			dprintk("DE-Engage mux for direct gain reg control\n");
			en_pwm_rf_mux = 0;
		} else
			dprintk("Engage mux for PWM control\n");

		dib0090_write_reg(state, 0x32, (en_pwm_rf_mux << 12) | (en_pwm_rf_mux << 11));

		/* Set fast servo cutoff to start AGC; 0 = 1KHz ; 1 = 50Hz ; 2 = 150Hz ; 3 = 50KHz ; 4 = servo fast*/
		if (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1)
			dib0090_write_reg(state, 0x04, 3);
		else
			dib0090_write_reg(state, 0x04, 1);
		dib0090_write_reg(state, 0x39, (1 << 10)); /* 0 gain by default */
	}
}