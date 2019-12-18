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
struct dvb_frontend {struct atbm_state* demodulator_priv; } ;
struct atbm_state {struct atbm8830_config* config; } ;
struct atbm8830_config {int /*<<< orphan*/  agc_hold_loop; int /*<<< orphan*/  agc_max; int /*<<< orphan*/  agc_min; int /*<<< orphan*/  if_freq; int /*<<< orphan*/  osc_clk_freq; } ;

/* Variables and functions */
 int REG_DEMOD_RUN ; 
 int /*<<< orphan*/  atbm8830_write_reg (struct atbm_state*,int,int) ; 
 int /*<<< orphan*/  set_agc_config (struct atbm_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_if_freq (struct atbm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_osc_freq (struct atbm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_static_channel_mode (struct atbm_state*) ; 
 int /*<<< orphan*/  set_ts_config (struct atbm_state*) ; 

__attribute__((used)) static int atbm8830_init(struct dvb_frontend *fe)
{
	struct atbm_state *priv = fe->demodulator_priv;
	const struct atbm8830_config *cfg = priv->config;

	/*Set oscillator frequency*/
	set_osc_freq(priv, cfg->osc_clk_freq);

	/*Set IF frequency*/
	set_if_freq(priv, cfg->if_freq);

	/*Set AGC Config*/
	set_agc_config(priv, cfg->agc_min, cfg->agc_max,
		cfg->agc_hold_loop);

	/*Set static channel mode*/
	set_static_channel_mode(priv);

	set_ts_config(priv);
	/*Turn off DSP reset*/
	atbm8830_write_reg(priv, 0x000A, 0);

	/*SW version test*/
	atbm8830_write_reg(priv, 0x020C, 11);

	/* Run */
	atbm8830_write_reg(priv, REG_DEMOD_RUN, 1);

	return 0;
}