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
struct tda10048_state {int dummy; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  modulation; } ;

/* Variables and functions */
 int EAGAIN ; 
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_5_6 ; 
 void* FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TDA10048_AUTO ; 
 int /*<<< orphan*/  TDA10048_OUT_CONF1 ; 
 int /*<<< orphan*/  TDA10048_OUT_CONF2 ; 
 int /*<<< orphan*/  TDA10048_OUT_CONF3 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int tda10048_readreg (struct tda10048_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda10048_get_tps(struct tda10048_state *state,
	struct dtv_frontend_properties *p)
{
	u8 val;

	/* Make sure the TPS regs are valid */
	if (!(tda10048_readreg(state, TDA10048_AUTO) & 0x01))
		return -EAGAIN;

	val = tda10048_readreg(state, TDA10048_OUT_CONF2);
	switch ((val & 0x60) >> 5) {
	case 0:
		p->modulation = QPSK;
		break;
	case 1:
		p->modulation = QAM_16;
		break;
	case 2:
		p->modulation = QAM_64;
		break;
	}
	switch ((val & 0x18) >> 3) {
	case 0:
		p->hierarchy = HIERARCHY_NONE;
		break;
	case 1:
		p->hierarchy = HIERARCHY_1;
		break;
	case 2:
		p->hierarchy = HIERARCHY_2;
		break;
	case 3:
		p->hierarchy = HIERARCHY_4;
		break;
	}
	switch (val & 0x07) {
	case 0:
		p->code_rate_HP = FEC_1_2;
		break;
	case 1:
		p->code_rate_HP = FEC_2_3;
		break;
	case 2:
		p->code_rate_HP = FEC_3_4;
		break;
	case 3:
		p->code_rate_HP = FEC_5_6;
		break;
	case 4:
		p->code_rate_HP = FEC_7_8;
		break;
	}

	val = tda10048_readreg(state, TDA10048_OUT_CONF3);
	switch (val & 0x07) {
	case 0:
		p->code_rate_LP = FEC_1_2;
		break;
	case 1:
		p->code_rate_LP = FEC_2_3;
		break;
	case 2:
		p->code_rate_LP = FEC_3_4;
		break;
	case 3:
		p->code_rate_LP = FEC_5_6;
		break;
	case 4:
		p->code_rate_LP = FEC_7_8;
		break;
	}

	val = tda10048_readreg(state, TDA10048_OUT_CONF1);
	switch ((val & 0x0c) >> 2) {
	case 0:
		p->guard_interval = GUARD_INTERVAL_1_32;
		break;
	case 1:
		p->guard_interval = GUARD_INTERVAL_1_16;
		break;
	case 2:
		p->guard_interval =  GUARD_INTERVAL_1_8;
		break;
	case 3:
		p->guard_interval =  GUARD_INTERVAL_1_4;
		break;
	}
	switch (val & 0x03) {
	case 0:
		p->transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		p->transmission_mode = TRANSMISSION_MODE_8K;
		break;
	}

	return 0;
}