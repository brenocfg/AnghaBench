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
struct dib7000p_state {scalar_t__ version; TYPE_1__ cfg; int /*<<< orphan*/  demod; } ;

/* Variables and functions */
#define  OUTMODE_ANALOG_ADC 134 
#define  OUTMODE_DIVERSITY 133 
#define  OUTMODE_HIGH_Z 132 
#define  OUTMODE_MPEG2_FIFO 131 
#define  OUTMODE_MPEG2_PAR_CONT_CLK 130 
#define  OUTMODE_MPEG2_PAR_GATED_CLK 129 
#define  OUTMODE_MPEG2_SERIAL 128 
 scalar_t__ SOC7090 ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static int dib7000p_set_output_mode(struct dib7000p_state *state, int mode)
{
	int ret = 0;
	u16 outreg, fifo_threshold, smo_mode;

	outreg = 0;
	fifo_threshold = 1792;
	smo_mode = (dib7000p_read_word(state, 235) & 0x0050) | (1 << 1);

	dprintk("setting output mode for demod %p to %d\n", &state->demod, mode);

	switch (mode) {
	case OUTMODE_MPEG2_PAR_GATED_CLK:
		outreg = (1 << 10);	/* 0x0400 */
		break;
	case OUTMODE_MPEG2_PAR_CONT_CLK:
		outreg = (1 << 10) | (1 << 6);	/* 0x0440 */
		break;
	case OUTMODE_MPEG2_SERIAL:
		outreg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0480 */
		break;
	case OUTMODE_DIVERSITY:
		if (state->cfg.hostbus_diversity)
			outreg = (1 << 10) | (4 << 6);	/* 0x0500 */
		else
			outreg = (1 << 11);
		break;
	case OUTMODE_MPEG2_FIFO:
		smo_mode |= (3 << 1);
		fifo_threshold = 512;
		outreg = (1 << 10) | (5 << 6);
		break;
	case OUTMODE_ANALOG_ADC:
		outreg = (1 << 10) | (3 << 6);
		break;
	case OUTMODE_HIGH_Z:
		outreg = 0;
		break;
	default:
		dprintk("Unhandled output_mode passed to be set for demod %p\n", &state->demod);
		break;
	}

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	ret |= dib7000p_write_word(state, 235, smo_mode);
	ret |= dib7000p_write_word(state, 236, fifo_threshold);	/* synchronous fread */
	if (state->version != SOC7090)
		ret |= dib7000p_write_word(state, 1286, outreg);	/* P_Div_active */

	return ret;
}