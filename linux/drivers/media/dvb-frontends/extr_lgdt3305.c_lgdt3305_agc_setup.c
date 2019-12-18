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
struct lgdt3305_state {TYPE_1__* cfg; } ;
struct dtv_frontend_properties {int modulation; } ;
struct TYPE_2__ {int demod_chip; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LGDT3304 132 
#define  LGDT3305 131 
 int LGDT3305_AGC_CTRL_1 ; 
 int LGDT3305_AGC_CTRL_4 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int,int) ; 
 int lgdt3305_rfagc_loop (struct lgdt3305_state*,struct dtv_frontend_properties*) ; 
 int /*<<< orphan*/  lgdt3305_set_reg_bit (struct lgdt3305_state*,int,int,int) ; 
 int /*<<< orphan*/  lgdt3305_write_reg (struct lgdt3305_state*,int,int) ; 

__attribute__((used)) static int lgdt3305_agc_setup(struct lgdt3305_state *state,
			      struct dtv_frontend_properties *p)
{
	int lockdten, acqen;

	switch (p->modulation) {
	case VSB_8:
		lockdten = 0;
		acqen = 0;
		break;
	case QAM_64:
	case QAM_256:
		lockdten = 1;
		acqen = 1;
		break;
	default:
		return -EINVAL;
	}

	lg_dbg("lockdten = %d, acqen = %d\n", lockdten, acqen);

	/* control agc function */
	switch (state->cfg->demod_chip) {
	case LGDT3304:
		lgdt3305_write_reg(state, 0x0314, 0xe1 | lockdten << 1);
		lgdt3305_set_reg_bit(state, 0x030e, 2, acqen);
		break;
	case LGDT3305:
		lgdt3305_write_reg(state, LGDT3305_AGC_CTRL_4, 0xe1 | lockdten << 1);
		lgdt3305_set_reg_bit(state, LGDT3305_AGC_CTRL_1, 2, acqen);
		break;
	default:
		return -EINVAL;
	}

	return lgdt3305_rfagc_loop(state, p);
}