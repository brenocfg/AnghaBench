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
struct TYPE_2__ {scalar_t__ output_mpeg2_in_188_bytes; int /*<<< orphan*/  hostbus_diversity; } ;
struct dib7000m_state {int reg_offs; int revision; TYPE_1__ cfg; int /*<<< orphan*/  demod; } ;

/* Variables and functions */
#define  OUTMODE_DIVERSITY 133 
#define  OUTMODE_HIGH_Z 132 
#define  OUTMODE_MPEG2_FIFO 131 
#define  OUTMODE_MPEG2_PAR_CONT_CLK 130 
#define  OUTMODE_MPEG2_PAR_GATED_CLK 129 
#define  OUTMODE_MPEG2_SERIAL 128 
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int dib7000m_write_word (struct dib7000m_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static int dib7000m_set_output_mode(struct dib7000m_state *state, int mode)
{
	int    ret = 0;
	u16 outreg, fifo_threshold, smo_mode,
		sram = 0x0005; /* by default SRAM output is disabled */

	outreg = 0;
	fifo_threshold = 1792;
	smo_mode = (dib7000m_read_word(state, 294 + state->reg_offs) & 0x0010) | (1 << 1);

	dprintk("setting output mode for demod %p to %d\n", &state->demod, mode);

	switch (mode) {
		case OUTMODE_MPEG2_PAR_GATED_CLK:   // STBs with parallel gated clock
			outreg = (1 << 10);  /* 0x0400 */
			break;
		case OUTMODE_MPEG2_PAR_CONT_CLK:    // STBs with parallel continues clock
			outreg = (1 << 10) | (1 << 6); /* 0x0440 */
			break;
		case OUTMODE_MPEG2_SERIAL:          // STBs with serial input
			outreg = (1 << 10) | (2 << 6) | (0 << 1); /* 0x0482 */
			break;
		case OUTMODE_DIVERSITY:
			if (state->cfg.hostbus_diversity)
				outreg = (1 << 10) | (4 << 6); /* 0x0500 */
			else
				sram   |= 0x0c00;
			break;
		case OUTMODE_MPEG2_FIFO:            // e.g. USB feeding
			smo_mode |= (3 << 1);
			fifo_threshold = 512;
			outreg = (1 << 10) | (5 << 6);
			break;
		case OUTMODE_HIGH_Z:  // disable
			outreg = 0;
			break;
		default:
			dprintk("Unhandled output_mode passed to be set for demod %p\n", &state->demod);
			break;
	}

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5) ;

	ret |= dib7000m_write_word(state,  294 + state->reg_offs, smo_mode);
	ret |= dib7000m_write_word(state,  295 + state->reg_offs, fifo_threshold); /* synchronous fread */
	ret |= dib7000m_write_word(state, 1795, outreg);
	ret |= dib7000m_write_word(state, 1805, sram);

	if (state->revision == 0x4003) {
		u16 clk_cfg1 = dib7000m_read_word(state, 909) & 0xfffd;
		if (mode == OUTMODE_DIVERSITY)
			clk_cfg1 |= (1 << 1); // P_O_CLK_en
		dib7000m_write_word(state, 909, clk_cfg1);
	}
	return ret;
}