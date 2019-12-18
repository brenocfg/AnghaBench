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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct lgdt3305_state {TYPE_1__* cfg; } ;
struct dtv_frontend_properties {int modulation; } ;
struct TYPE_2__ {int vsb_if_khz; int qam_if_khz; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_CR_CTR_FREQ_1 ; 
 int /*<<< orphan*/  LGDT3305_CR_CTR_FREQ_2 ; 
 int /*<<< orphan*/  LGDT3305_CR_CTR_FREQ_3 ; 
 int /*<<< orphan*/  LGDT3305_CR_CTR_FREQ_4 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  lg_dbg (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3305_set_if(struct lgdt3305_state *state,
			   struct dtv_frontend_properties *p)
{
	u16 if_freq_khz;
	u8 nco1, nco2, nco3, nco4;
	u64 nco;

	switch (p->modulation) {
	case VSB_8:
		if_freq_khz = state->cfg->vsb_if_khz;
		break;
	case QAM_64:
	case QAM_256:
		if_freq_khz = state->cfg->qam_if_khz;
		break;
	default:
		return -EINVAL;
	}

	nco = if_freq_khz / 10;

	switch (p->modulation) {
	case VSB_8:
		nco <<= 24;
		do_div(nco, 625);
		break;
	case QAM_64:
	case QAM_256:
		nco <<= 28;
		do_div(nco, 625);
		break;
	default:
		return -EINVAL;
	}

	nco1 = (nco >> 24) & 0x3f;
	nco1 |= 0x40;
	nco2 = (nco >> 16) & 0xff;
	nco3 = (nco >> 8) & 0xff;
	nco4 = nco & 0xff;

	lgdt3305_write_reg(state, LGDT3305_CR_CTR_FREQ_1, nco1);
	lgdt3305_write_reg(state, LGDT3305_CR_CTR_FREQ_2, nco2);
	lgdt3305_write_reg(state, LGDT3305_CR_CTR_FREQ_3, nco3);
	lgdt3305_write_reg(state, LGDT3305_CR_CTR_FREQ_4, nco4);

	lg_dbg("%d KHz -> [%02x%02x%02x%02x]\n",
	       if_freq_khz, nco1, nco2, nco3, nco4);

	return 0;
}