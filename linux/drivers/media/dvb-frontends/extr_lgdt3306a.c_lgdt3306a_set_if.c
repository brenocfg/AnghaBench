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
typedef  int u16 ;
struct lgdt3306a_state {TYPE_1__* cfg; } ;
struct dtv_frontend_properties {int modulation; } ;
struct TYPE_2__ {int vsb_if_khz; int qam_if_khz; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QAM_256 131 
#define  QAM_64 130 
#define  QAM_AUTO 129 
#define  VSB_8 128 
 int /*<<< orphan*/  dbg_info (char*,int,int) ; 
 int lgdt3306a_write_reg (struct lgdt3306a_state*,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int lgdt3306a_set_if(struct lgdt3306a_state *state,
			   struct dtv_frontend_properties *p)
{
	int ret;
	u16 if_freq_khz;
	u8 nco1, nco2;

	switch (p->modulation) {
	case VSB_8:
		if_freq_khz = state->cfg->vsb_if_khz;
		break;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		if_freq_khz = state->cfg->qam_if_khz;
		break;
	default:
		return -EINVAL;
	}

	switch (if_freq_khz) {
	default:
		pr_warn("IF=%d KHz is not supported, 3250 assumed\n",
			if_freq_khz);
		/* fallthrough */
	case 3250: /* 3.25Mhz */
		nco1 = 0x34;
		nco2 = 0x00;
		break;
	case 3500: /* 3.50Mhz */
		nco1 = 0x38;
		nco2 = 0x00;
		break;
	case 4000: /* 4.00Mhz */
		nco1 = 0x40;
		nco2 = 0x00;
		break;
	case 5000: /* 5.00Mhz */
		nco1 = 0x50;
		nco2 = 0x00;
		break;
	case 5380: /* 5.38Mhz */
		nco1 = 0x56;
		nco2 = 0x14;
		break;
	}
	ret = lgdt3306a_write_reg(state, 0x0010, nco1);
	if (ret)
		return ret;
	ret = lgdt3306a_write_reg(state, 0x0011, nco2);
	if (ret)
		return ret;

	dbg_info("if_freq=%d KHz->[%04x]\n", if_freq_khz, nco1<<8 | nco2);

	return 0;
}