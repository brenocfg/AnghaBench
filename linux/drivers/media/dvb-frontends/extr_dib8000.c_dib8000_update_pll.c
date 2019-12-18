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
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dibx000_bandwidth_config {int pll_prediv; int pll_ratio; } ;
struct TYPE_4__ {TYPE_1__* pll; } ;
struct dib8000_state {int revision; int current_demod_bw; TYPE_2__ cfg; } ;
struct TYPE_3__ {int pll_prediv; int pll_ratio; } ;

/* Variables and functions */
 int EINVAL ; 
 int dib8000_read32 (struct dib8000_state*,int) ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_reset_pll (struct dib8000_state*) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int dib8000_update_pll(struct dvb_frontend *fe,
		struct dibx000_bandwidth_config *pll, u32 bw, u8 ratio)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 reg_1857, reg_1856 = dib8000_read_word(state, 1856);
	u8 loopdiv, prediv, oldprediv = state->cfg.pll->pll_prediv ;
	u32 internal, xtal;

	/* get back old values */
	prediv = reg_1856 & 0x3f;
	loopdiv = (reg_1856 >> 6) & 0x3f;

	if ((pll == NULL) || (pll->pll_prediv == prediv &&
				pll->pll_ratio == loopdiv))
		return -EINVAL;

	dprintk("Updating pll (prediv: old =  %d new = %d ; loopdiv : old = %d new = %d)\n", prediv, pll->pll_prediv, loopdiv, pll->pll_ratio);
	if (state->revision == 0x8090) {
		reg_1856 &= 0xf000;
		reg_1857 = dib8000_read_word(state, 1857);
		/* disable PLL */
		dib8000_write_word(state, 1857, reg_1857 & ~(1 << 15));

		dib8000_write_word(state, 1856, reg_1856 |
				((pll->pll_ratio & 0x3f) << 6) |
				(pll->pll_prediv & 0x3f));

		/* write new system clk into P_sec_len */
		internal = dib8000_read32(state, 23) / 1000;
		dprintk("Old Internal = %d\n", internal);
		xtal = 2 * (internal / loopdiv) * prediv;
		internal = 1000 * (xtal/pll->pll_prediv) * pll->pll_ratio;
		dprintk("Xtal = %d , New Fmem = %d New Fdemod = %d, New Fsampling = %d\n", xtal, internal/1000, internal/2000, internal/8000);
		dprintk("New Internal = %d\n", internal);

		dib8000_write_word(state, 23,
				(u16) (((internal / 2) >> 16) & 0xffff));
		dib8000_write_word(state, 24, (u16) ((internal / 2) & 0xffff));
		/* enable PLL */
		dib8000_write_word(state, 1857, reg_1857 | (1 << 15));

		while (((dib8000_read_word(state, 1856)>>15)&0x1) != 1)
			dprintk("Waiting for PLL to lock\n");

		/* verify */
		reg_1856 = dib8000_read_word(state, 1856);
		dprintk("PLL Updated with prediv = %d and loopdiv = %d\n",
				reg_1856&0x3f, (reg_1856>>6)&0x3f);
	} else {
		if (bw != state->current_demod_bw) {
			/** Bandwidth change => force PLL update **/
			dprintk("PLL: Bandwidth Change %d MHz -> %d MHz (prediv: %d->%d)\n", state->current_demod_bw / 1000, bw / 1000, oldprediv, state->cfg.pll->pll_prediv);

			if (state->cfg.pll->pll_prediv != oldprediv) {
				/** Full PLL change only if prediv is changed **/

				/** full update => bypass and reconfigure **/
				dprintk("PLL: New Setting for %d MHz Bandwidth (prediv: %d, ratio: %d)\n", bw/1000, state->cfg.pll->pll_prediv, state->cfg.pll->pll_ratio);
				dib8000_write_word(state, 902, dib8000_read_word(state, 902) | (1<<3)); /* bypass PLL */
				dib8000_reset_pll(state);
				dib8000_write_word(state, 898, 0x0004); /* sad */
			} else
				ratio = state->cfg.pll->pll_ratio;

			state->current_demod_bw = bw;
		}

		if (ratio != 0) {
			/** ratio update => only change ratio **/
			dprintk("PLL: Update ratio (prediv: %d, ratio: %d)\n", state->cfg.pll->pll_prediv, ratio);
			dib8000_write_word(state, 901, (state->cfg.pll->pll_prediv << 8) | (ratio << 0)); /* only the PLL ratio is updated. */
		}
	}

	return 0;
}