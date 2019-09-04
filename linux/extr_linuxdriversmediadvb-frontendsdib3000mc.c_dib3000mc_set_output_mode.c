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
struct dib3000mc_state {TYPE_1__* cfg; int /*<<< orphan*/  demod; } ;
struct TYPE_2__ {scalar_t__ output_mpeg2_in_188_bytes; } ;

/* Variables and functions */
#define  OUTMODE_DIVERSITY 133 
#define  OUTMODE_HIGH_Z 132 
#define  OUTMODE_MPEG2_FIFO 131 
#define  OUTMODE_MPEG2_PAR_CONT_CLK 130 
#define  OUTMODE_MPEG2_PAR_GATED_CLK 129 
#define  OUTMODE_MPEG2_SERIAL 128 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static int dib3000mc_set_output_mode(struct dib3000mc_state *state, int mode)
{
	int    ret = 0;
	u16 fifo_threshold = 1792;
	u16 outreg = 0;
	u16 outmode = 0;
	u16 elecout = 1;
	u16 smo_reg = dib3000mc_read_word(state, 206) & 0x0010; /* keep the pid_parse bit */

	dprintk("-I-  Setting output mode for demod %p to %d\n",
			&state->demod, mode);

	switch (mode) {
		case OUTMODE_HIGH_Z:  // disable
			elecout = 0;
			break;
		case OUTMODE_MPEG2_PAR_GATED_CLK:   // STBs with parallel gated clock
			outmode = 0;
			break;
		case OUTMODE_MPEG2_PAR_CONT_CLK:    // STBs with parallel continues clock
			outmode = 1;
			break;
		case OUTMODE_MPEG2_SERIAL:          // STBs with serial input
			outmode = 2;
			break;
		case OUTMODE_MPEG2_FIFO:            // e.g. USB feeding
			elecout = 3;
			/*ADDR @ 206 :
			P_smo_error_discard  [1;6:6] = 0
			P_smo_rs_discard     [1;5:5] = 0
			P_smo_pid_parse      [1;4:4] = 0
			P_smo_fifo_flush     [1;3:3] = 0
			P_smo_mode           [2;2:1] = 11
			P_smo_ovf_prot       [1;0:0] = 0
			*/
			smo_reg |= 3 << 1;
			fifo_threshold = 512;
			outmode = 5;
			break;
		case OUTMODE_DIVERSITY:
			outmode = 4;
			elecout = 1;
			break;
		default:
			dprintk("Unhandled output_mode passed to be set for demod %p\n",&state->demod);
			outmode = 0;
			break;
	}

	if ((state->cfg->output_mpeg2_in_188_bytes))
		smo_reg |= (1 << 5); // P_smo_rs_discard     [1;5:5] = 1

	outreg = dib3000mc_read_word(state, 244) & 0x07FF;
	outreg |= (outmode << 11);
	ret |= dib3000mc_write_word(state,  244, outreg);
	ret |= dib3000mc_write_word(state,  206, smo_reg);   /*smo_ mode*/
	ret |= dib3000mc_write_word(state,  207, fifo_threshold); /* synchronous fread */
	ret |= dib3000mc_write_word(state, 1040, elecout);         /* P_out_cfg */
	return ret;
}