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
struct TYPE_2__ {int usref_8vsb; int usref_qam64; int usref_qam256; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_AGC_CTRL_1 ; 
 int /*<<< orphan*/  LGDT3305_AGC_POWER_REF_1 ; 
 int /*<<< orphan*/  LGDT3305_AGC_POWER_REF_2 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int) ; 
 int /*<<< orphan*/  lgdt3305_set_reg_bit (struct lgdt3305_state*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3305_set_agc_power_ref(struct lgdt3305_state *state,
				      struct dtv_frontend_properties *p)
{
	u16 usref = 0;

	switch (p->modulation) {
	case VSB_8:
		if (state->cfg->usref_8vsb)
			usref = state->cfg->usref_8vsb;
		break;
	case QAM_64:
		if (state->cfg->usref_qam64)
			usref = state->cfg->usref_qam64;
		break;
	case QAM_256:
		if (state->cfg->usref_qam256)
			usref = state->cfg->usref_qam256;
		break;
	default:
		return -EINVAL;
	}

	if (usref) {
		lg_dbg("set manual mode: 0x%04x\n", usref);

		lgdt3305_set_reg_bit(state, LGDT3305_AGC_CTRL_1, 3, 1);

		lgdt3305_write_reg(state, LGDT3305_AGC_POWER_REF_1,
				   0xff & (usref >> 8));
		lgdt3305_write_reg(state, LGDT3305_AGC_POWER_REF_2,
				   0xff & (usref >> 0));
	}
	return 0;
}