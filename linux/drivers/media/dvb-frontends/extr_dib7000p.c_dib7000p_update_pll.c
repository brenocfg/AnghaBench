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
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dibx000_bandwidth_config {int pll_prediv; int pll_ratio; } ;
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int dib7000p_get_internal_freq (struct dib7000p_state*) ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int dib7000p_update_pll(struct dvb_frontend *fe, struct dibx000_bandwidth_config *bw)
{
	struct dib7000p_state *state = fe->demodulator_priv;
	u16 reg_1857, reg_1856 = dib7000p_read_word(state, 1856);
	u8 loopdiv, prediv;
	u32 internal, xtal;

	/* get back old values */
	prediv = reg_1856 & 0x3f;
	loopdiv = (reg_1856 >> 6) & 0x3f;

	if ((bw != NULL) && (bw->pll_prediv != prediv || bw->pll_ratio != loopdiv)) {
		dprintk("Updating pll (prediv: old =  %d new = %d ; loopdiv : old = %d new = %d)\n", prediv, bw->pll_prediv, loopdiv, bw->pll_ratio);
		reg_1856 &= 0xf000;
		reg_1857 = dib7000p_read_word(state, 1857);
		dib7000p_write_word(state, 1857, reg_1857 & ~(1 << 15));

		dib7000p_write_word(state, 1856, reg_1856 | ((bw->pll_ratio & 0x3f) << 6) | (bw->pll_prediv & 0x3f));

		/* write new system clk into P_sec_len */
		internal = dib7000p_get_internal_freq(state);
		xtal = (internal / loopdiv) * prediv;
		internal = 1000 * (xtal / bw->pll_prediv) * bw->pll_ratio;	/* new internal */
		dib7000p_write_word(state, 18, (u16) ((internal >> 16) & 0xffff));
		dib7000p_write_word(state, 19, (u16) (internal & 0xffff));

		dib7000p_write_word(state, 1857, reg_1857 | (1 << 15));

		while (((dib7000p_read_word(state, 1856) >> 15) & 0x1) != 1)
			dprintk("Waiting for PLL to lock\n");

		return 0;
	}
	return -EIO;
}