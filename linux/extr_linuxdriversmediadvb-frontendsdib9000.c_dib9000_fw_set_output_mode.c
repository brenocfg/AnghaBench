#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_mpeg2_in_188_bytes; } ;
struct TYPE_5__ {TYPE_1__ cfg; } ;
struct TYPE_6__ {TYPE_2__ d9; } ;
struct dib9000_state {TYPE_3__ chip; int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OUTMODE_DIVERSITY 133 
#define  OUTMODE_HIGH_Z 132 
#define  OUTMODE_MPEG2_FIFO 131 
#define  OUTMODE_MPEG2_PAR_CONT_CLK 130 
#define  OUTMODE_MPEG2_PAR_GATED_CLK 129 
#define  OUTMODE_MPEG2_SERIAL 128 
 int /*<<< orphan*/  OUT_MSG_SET_OUTPUT_MODE ; 
 int dib9000_mbx_send (struct dib9000_state*,int /*<<< orphan*/ ,int*,int) ; 
 int dib9000_read_word (struct dib9000_state*,int) ; 
 int /*<<< orphan*/  dib9000_write_word (struct dib9000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,struct dvb_frontend*,...) ; 
 int to_fw_output_mode (int) ; 

__attribute__((used)) static int dib9000_fw_set_output_mode(struct dvb_frontend *fe, int mode)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u16 outreg, smo_mode;

	dprintk("setting output mode for demod %p to %d\n", fe, mode);

	switch (mode) {
	case OUTMODE_MPEG2_PAR_GATED_CLK:
		outreg = (1 << 10);	/* 0x0400 */
		break;
	case OUTMODE_MPEG2_PAR_CONT_CLK:
		outreg = (1 << 10) | (1 << 6);	/* 0x0440 */
		break;
	case OUTMODE_MPEG2_SERIAL:
		outreg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0482 */
		break;
	case OUTMODE_DIVERSITY:
		outreg = (1 << 10) | (4 << 6);	/* 0x0500 */
		break;
	case OUTMODE_MPEG2_FIFO:
		outreg = (1 << 10) | (5 << 6);
		break;
	case OUTMODE_HIGH_Z:
		outreg = 0;
		break;
	default:
		dprintk("Unhandled output_mode passed to be set for demod %p\n", &state->fe[0]);
		return -EINVAL;
	}

	dib9000_write_word(state, 1795, outreg);

	switch (mode) {
	case OUTMODE_MPEG2_PAR_GATED_CLK:
	case OUTMODE_MPEG2_PAR_CONT_CLK:
	case OUTMODE_MPEG2_SERIAL:
	case OUTMODE_MPEG2_FIFO:
		smo_mode = (dib9000_read_word(state, 295) & 0x0010) | (1 << 1);
		if (state->chip.d9.cfg.output_mpeg2_in_188_bytes)
			smo_mode |= (1 << 5);
		dib9000_write_word(state, 295, smo_mode);
		break;
	}

	outreg = to_fw_output_mode(mode);
	return dib9000_mbx_send(state, OUT_MSG_SET_OUTPUT_MODE, &outreg, 1);
}