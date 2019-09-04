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
struct lgdt3305_state {TYPE_1__* cfg; } ;
struct dtv_frontend_properties {int modulation; } ;
struct TYPE_2__ {scalar_t__ rf_agc_loop; int /*<<< orphan*/  demod_chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3304 ; 
 int /*<<< orphan*/  LGDT3305_AGC_DELAY_PT_1 ; 
 int /*<<< orphan*/  LGDT3305_AGC_DELAY_PT_2 ; 
 int /*<<< orphan*/  LGDT3305_IFBW_1 ; 
 int /*<<< orphan*/  LGDT3305_IFBW_2 ; 
 int /*<<< orphan*/  LGDT3305_RFAGC_LOOP_FLTR_BW_1 ; 
 int /*<<< orphan*/  LGDT3305_RFAGC_LOOP_FLTR_BW_2 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int,...) ; 
 int /*<<< orphan*/  lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3305_rfagc_loop(struct lgdt3305_state *state,
			       struct dtv_frontend_properties *p)
{
	u16 ifbw, rfbw, agcdelay;

	switch (p->modulation) {
	case VSB_8:
		agcdelay = 0x04c0;
		rfbw     = 0x8000;
		ifbw     = 0x8000;
		break;
	case QAM_64:
	case QAM_256:
		agcdelay = 0x046b;
		rfbw     = 0x8889;
		/* FIXME: investigate optimal ifbw & rfbw values for the
		 *        DT3304 and re-write this switch..case block */
		if (state->cfg->demod_chip == LGDT3304)
			ifbw = 0x6666;
		else /* (state->cfg->demod_chip == LGDT3305) */
			ifbw = 0x8888;
		break;
	default:
		return -EINVAL;
	}

	if (state->cfg->rf_agc_loop) {
		lg_dbg("agcdelay: 0x%04x, rfbw: 0x%04x\n", agcdelay, rfbw);

		/* rf agc loop filter bandwidth */
		lgdt3305_write_reg(state, LGDT3305_AGC_DELAY_PT_1,
				   agcdelay >> 8);
		lgdt3305_write_reg(state, LGDT3305_AGC_DELAY_PT_2,
				   agcdelay & 0xff);

		lgdt3305_write_reg(state, LGDT3305_RFAGC_LOOP_FLTR_BW_1,
				   rfbw >> 8);
		lgdt3305_write_reg(state, LGDT3305_RFAGC_LOOP_FLTR_BW_2,
				   rfbw & 0xff);
	} else {
		lg_dbg("ifbw: 0x%04x\n", ifbw);

		/* if agc loop filter bandwidth */
		lgdt3305_write_reg(state, LGDT3305_IFBW_1, ifbw >> 8);
		lgdt3305_write_reg(state, LGDT3305_IFBW_2, ifbw & 0xff);
	}

	return 0;
}