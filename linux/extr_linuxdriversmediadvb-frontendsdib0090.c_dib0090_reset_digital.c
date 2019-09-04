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
typedef  int u16 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {int dummy; } ;
struct TYPE_2__ {int adc_clock_ratio; int pll_range; int pll_loopdiv; int pll_prediv; int pll_bypass; } ;
struct dib0090_config {int clkoutdrive; int clkouttobamse; TYPE_1__ io; scalar_t__ in_soc; int /*<<< orphan*/  analog_output; } ;

/* Variables and functions */
 int EN_CRYSTAL ; 
 int EN_DIGCLK ; 
 int EN_PLL ; 
 int /*<<< orphan*/  HARD_RESET (struct dib0090_state*) ; 
 int dib0090_read_reg (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static void dib0090_reset_digital(struct dvb_frontend *fe, const struct dib0090_config *cfg)
{
	struct dib0090_state *state = fe->tuner_priv;
	u16 PllCfg, i, v;

	HARD_RESET(state);
	dib0090_write_reg(state, 0x24, EN_PLL | EN_CRYSTAL);
	if (cfg->in_soc)
		return;

	dib0090_write_reg(state, 0x1b, EN_DIGCLK | EN_PLL | EN_CRYSTAL);	/* PLL, DIG_CLK and CRYSTAL remain */
	/* adcClkOutRatio=8->7, release reset */
	dib0090_write_reg(state, 0x20, ((cfg->io.adc_clock_ratio - 1) << 11) | (0 << 10) | (1 << 9) | (1 << 8) | (0 << 4) | 0);
	if (cfg->clkoutdrive != 0)
		dib0090_write_reg(state, 0x23, (0 << 15) | ((!cfg->analog_output) << 14) | (2 << 10) | (1 << 9) | (0 << 8)
				| (cfg->clkoutdrive << 5) | (cfg->clkouttobamse << 4) | (0 << 2) | (0));
	else
		dib0090_write_reg(state, 0x23, (0 << 15) | ((!cfg->analog_output) << 14) | (2 << 10) | (1 << 9) | (0 << 8)
				| (7 << 5) | (cfg->clkouttobamse << 4) | (0 << 2) | (0));

	/* Read Pll current config * */
	PllCfg = dib0090_read_reg(state, 0x21);

	/** Reconfigure PLL if current setting is different from default setting **/
	if ((PllCfg & 0x1FFF) != ((cfg->io.pll_range << 12) | (cfg->io.pll_loopdiv << 6) | (cfg->io.pll_prediv)) && (!cfg->in_soc)
			&& !cfg->io.pll_bypass) {

		/* Set Bypass mode */
		PllCfg |= (1 << 15);
		dib0090_write_reg(state, 0x21, PllCfg);

		/* Set Reset Pll */
		PllCfg &= ~(1 << 13);
		dib0090_write_reg(state, 0x21, PllCfg);

	/*** Set new Pll configuration in bypass and reset state ***/
		PllCfg = (1 << 15) | (0 << 13) | (cfg->io.pll_range << 12) | (cfg->io.pll_loopdiv << 6) | (cfg->io.pll_prediv);
		dib0090_write_reg(state, 0x21, PllCfg);

		/* Remove Reset Pll */
		PllCfg |= (1 << 13);
		dib0090_write_reg(state, 0x21, PllCfg);

	/*** Wait for PLL lock ***/
		i = 100;
		do {
			v = !!(dib0090_read_reg(state, 0x1a) & 0x800);
			if (v)
				break;
		} while (--i);

		if (i == 0) {
			dprintk("Pll: Unable to lock Pll\n");
			return;
		}

		/* Finally Remove Bypass mode */
		PllCfg &= ~(1 << 15);
		dib0090_write_reg(state, 0x21, PllCfg);
	}

	if (cfg->io.pll_bypass) {
		PllCfg |= (cfg->io.pll_bypass << 15);
		dib0090_write_reg(state, 0x21, PllCfg);
	}
}