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
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; } ;
struct dibx000_agc_config {int agc1_max; int agc1_min; int agc2_max; int agc2_min; int agc1_pt1; int agc1_pt2; int agc1_slope1; int agc1_slope2; int agc2_pt1; int agc2_pt2; int agc2_slope1; int agc2_slope2; } ;
struct dib3000mc_state {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ phase_noise_mode; int max_time; int agc_command1; int agc_command2; int pwm3_value; int ln_adc_level; scalar_t__ mobile_mode; struct dibx000_agc_config* agc; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTMODE_HIGH_Z ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  dib3000mc_set_bandwidth (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_set_impulse_noise (struct dib3000mc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_set_output_mode (struct dib3000mc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_setup_pwm_state (struct dib3000mc_state*) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 

__attribute__((used)) static int dib3000mc_init(struct dvb_frontend *demod)
{
	struct dib3000mc_state *state = demod->demodulator_priv;
	struct dibx000_agc_config *agc = state->cfg->agc;

	// Restart Configuration
	dib3000mc_write_word(state, 1027, 0x8000);
	dib3000mc_write_word(state, 1027, 0x0000);

	// power up the demod + mobility configuration
	dib3000mc_write_word(state, 140, 0x0000);
	dib3000mc_write_word(state, 1031, 0);

	if (state->cfg->mobile_mode) {
		dib3000mc_write_word(state, 139,  0x0000);
		dib3000mc_write_word(state, 141,  0x0000);
		dib3000mc_write_word(state, 175,  0x0002);
		dib3000mc_write_word(state, 1032, 0x0000);
	} else {
		dib3000mc_write_word(state, 139,  0x0001);
		dib3000mc_write_word(state, 141,  0x0000);
		dib3000mc_write_word(state, 175,  0x0000);
		dib3000mc_write_word(state, 1032, 0x012C);
	}
	dib3000mc_write_word(state, 1033, 0x0000);

	// P_clk_cfg
	dib3000mc_write_word(state, 1037, 0x3130);

	// other configurations

	// P_ctrl_sfreq
	dib3000mc_write_word(state, 33, (5 << 0));
	dib3000mc_write_word(state, 88, (1 << 10) | (0x10 << 0));

	// Phase noise control
	// P_fft_phacor_inh, P_fft_phacor_cpe, P_fft_powrange
	dib3000mc_write_word(state, 99, (1 << 9) | (0x20 << 0));

	if (state->cfg->phase_noise_mode == 0)
		dib3000mc_write_word(state, 111, 0x00);
	else
		dib3000mc_write_word(state, 111, 0x02);

	// P_agc_global
	dib3000mc_write_word(state, 50, 0x8000);

	// agc setup misc
	dib3000mc_setup_pwm_state(state);

	// P_agc_counter_lock
	dib3000mc_write_word(state, 53, 0x87);
	// P_agc_counter_unlock
	dib3000mc_write_word(state, 54, 0x87);

	/* agc */
	dib3000mc_write_word(state, 36, state->cfg->max_time);
	dib3000mc_write_word(state, 37, (state->cfg->agc_command1 << 13) | (state->cfg->agc_command2 << 12) | (0x1d << 0));
	dib3000mc_write_word(state, 38, state->cfg->pwm3_value);
	dib3000mc_write_word(state, 39, state->cfg->ln_adc_level);

	// set_agc_loop_Bw
	dib3000mc_write_word(state, 40, 0x0179);
	dib3000mc_write_word(state, 41, 0x03f0);

	dib3000mc_write_word(state, 42, agc->agc1_max);
	dib3000mc_write_word(state, 43, agc->agc1_min);
	dib3000mc_write_word(state, 44, agc->agc2_max);
	dib3000mc_write_word(state, 45, agc->agc2_min);
	dib3000mc_write_word(state, 46, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib3000mc_write_word(state, 47, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib3000mc_write_word(state, 48, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib3000mc_write_word(state, 49, (agc->agc2_slope1 << 8) | agc->agc2_slope2);

// Begin: TimeOut registers
	// P_pha3_thres
	dib3000mc_write_word(state, 110, 3277);
	// P_timf_alpha = 6, P_corm_alpha = 6, P_corm_thres = 0x80
	dib3000mc_write_word(state,  26, 0x6680);
	// lock_mask0
	dib3000mc_write_word(state, 1, 4);
	// lock_mask1
	dib3000mc_write_word(state, 2, 4);
	// lock_mask2
	dib3000mc_write_word(state, 3, 0x1000);
	// P_search_maxtrial=1
	dib3000mc_write_word(state, 5, 1);

	dib3000mc_set_bandwidth(state, 8000);

	// div_lock_mask
	dib3000mc_write_word(state,  4, 0x814);

	dib3000mc_write_word(state, 21, (1 << 9) | 0x164);
	dib3000mc_write_word(state, 22, 0x463d);

	// Spurious rm cfg
	// P_cspu_regul, P_cspu_win_cut
	dib3000mc_write_word(state, 120, 0x200f);
	// P_adp_selec_monit
	dib3000mc_write_word(state, 134, 0);

	// Fec cfg
	dib3000mc_write_word(state, 195, 0x10);

	// diversity register: P_dvsy_sync_wait..
	dib3000mc_write_word(state, 180, 0x2FF0);

	// Impulse noise configuration
	dib3000mc_set_impulse_noise(state, 0, TRANSMISSION_MODE_8K);

	// output mode set-up
	dib3000mc_set_output_mode(state, OUTMODE_HIGH_Z);

	/* close the i2c-gate */
	dib3000mc_write_word(state, 769, (1 << 7) );

	return 0;
}