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
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct TYPE_4__ {int drives; int div_cfg; TYPE_1__* pll; } ;
struct dib8000_state {int revision; TYPE_2__ cfg; scalar_t__ isdbt_cfg_loaded; int /*<<< orphan*/ * current_agc; int /*<<< orphan*/  i2c_master; int /*<<< orphan*/  i2c; } ;
struct TYPE_3__ {scalar_t__ ifreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB8000_POWER_ALL ; 
 int /*<<< orphan*/  DIB8000_POWER_INTERFACE_ONLY ; 
 int /*<<< orphan*/  DIBX000_ADC_OFF ; 
 int /*<<< orphan*/  DIBX000_SLOW_ADC_OFF ; 
 int /*<<< orphan*/  DIBX000_SLOW_ADC_ON ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUTMODE_HIGH_Z ; 
 int* dib8000_defaults ; 
 int dib8000_identify (int /*<<< orphan*/ *) ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 scalar_t__ dib8000_reset_gpio (struct dib8000_state*) ; 
 int /*<<< orphan*/  dib8000_reset_pll (struct dib8000_state*) ; 
 int /*<<< orphan*/  dib8000_reset_stats (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib8000_sad_calib (struct dib8000_state*) ; 
 int /*<<< orphan*/  dib8000_set_adc_state (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_set_bandwidth (struct dvb_frontend*,int) ; 
 scalar_t__ dib8000_set_output_mode (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_set_power_mode (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dibx000_reset_i2c_master (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib8000_reset(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;

	if ((state->revision = dib8000_identify(&state->i2c)) == 0)
		return -EINVAL;

	/* sram lead in, rdy */
	if (state->revision != 0x8090)
		dib8000_write_word(state, 1287, 0x0003);

	if (state->revision == 0x8000)
		dprintk("error : dib8000 MA not supported\n");

	dibx000_reset_i2c_master(&state->i2c_master);

	dib8000_set_power_mode(state, DIB8000_POWER_ALL);

	/* always leave the VBG voltage on - it consumes almost nothing but takes a long time to start */
	dib8000_set_adc_state(state, DIBX000_ADC_OFF);

	/* restart all parts */
	dib8000_write_word(state, 770, 0xffff);
	dib8000_write_word(state, 771, 0xffff);
	dib8000_write_word(state, 772, 0xfffc);
	dib8000_write_word(state, 898, 0x000c);	/* restart sad */
	if (state->revision == 0x8090)
		dib8000_write_word(state, 1280, 0x0045);
	else
		dib8000_write_word(state, 1280, 0x004d);
	dib8000_write_word(state, 1281, 0x000c);

	dib8000_write_word(state, 770, 0x0000);
	dib8000_write_word(state, 771, 0x0000);
	dib8000_write_word(state, 772, 0x0000);
	dib8000_write_word(state, 898, 0x0004);	// sad
	dib8000_write_word(state, 1280, 0x0000);
	dib8000_write_word(state, 1281, 0x0000);

	/* drives */
	if (state->revision != 0x8090) {
		if (state->cfg.drives)
			dib8000_write_word(state, 906, state->cfg.drives);
		else {
			dprintk("using standard PAD-drive-settings, please adjust settings in config-struct to be optimal.\n");
			/* min drive SDRAM - not optimal - adjust */
			dib8000_write_word(state, 906, 0x2d98);
		}
	}

	dib8000_reset_pll(state);
	if (state->revision != 0x8090)
		dib8000_write_word(state, 898, 0x0004);

	if (dib8000_reset_gpio(state) != 0)
		dprintk("GPIO reset was not successful.\n");

	if ((state->revision != 0x8090) &&
			(dib8000_set_output_mode(fe, OUTMODE_HIGH_Z) != 0))
		dprintk("OUTPUT_MODE could not be reset.\n");

	state->current_agc = NULL;

	// P_iqc_alpha_pha, P_iqc_alpha_amp, P_iqc_dcc_alpha, ...
	/* P_iqc_ca2 = 0; P_iqc_impnc_on = 0; P_iqc_mode = 0; */
	if (state->cfg.pll->ifreq == 0)
		dib8000_write_word(state, 40, 0x0755);	/* P_iqc_corr_inh = 0 enable IQcorr block */
	else
		dib8000_write_word(state, 40, 0x1f55);	/* P_iqc_corr_inh = 1 disable IQcorr block */

	{
		u16 l = 0, r;
		const u16 *n;
		n = dib8000_defaults;
		l = *n++;
		while (l) {
			r = *n++;
			do {
				dib8000_write_word(state, r, *n++);
				r++;
			} while (--l);
			l = *n++;
		}
	}

	state->isdbt_cfg_loaded = 0;

	//div_cfg override for special configs
	if ((state->revision != 8090) && (state->cfg.div_cfg != 0))
		dib8000_write_word(state, 903, state->cfg.div_cfg);

	/* unforce divstr regardless whether i2c enumeration was done or not */
	dib8000_write_word(state, 1285, dib8000_read_word(state, 1285) & ~(1 << 1));

	dib8000_set_bandwidth(fe, 6000);

	dib8000_set_adc_state(state, DIBX000_SLOW_ADC_ON);
	dib8000_sad_calib(state);
	if (state->revision != 0x8090)
		dib8000_set_adc_state(state, DIBX000_SLOW_ADC_OFF);

	/* ber_rs_len = 3 */
	dib8000_write_word(state, 285, (dib8000_read_word(state, 285) & ~0x60) | (3 << 5));

	dib8000_set_power_mode(state, DIB8000_POWER_INTERFACE_ONLY);

	dib8000_reset_stats(fe);

	return 0;
}