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
struct dvb_frontend {struct as102_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  modulation; } ;
struct as10x_tps {int modulation; int hierarchy; int code_rate_HP; int code_rate_LP; int guard_interval; int transmission_mode; int /*<<< orphan*/  member_0; } ;
struct as102_state {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_tps ) (int /*<<< orphan*/ ,struct as10x_tps*) ;} ;

/* Variables and functions */
#define  CODE_RATE_1_2 145 
#define  CODE_RATE_2_3 144 
#define  CODE_RATE_3_4 143 
#define  CODE_RATE_5_6 142 
#define  CODE_RATE_7_8 141 
#define  CONST_QAM16 140 
#define  CONST_QAM64 139 
#define  CONST_QPSK 138 
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_5_6 ; 
 void* FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
#define  GUARD_INT_1_16 137 
#define  GUARD_INT_1_32 136 
#define  GUARD_INT_1_4 135 
#define  GUARD_INT_1_8 134 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
#define  HIER_ALPHA_1 133 
#define  HIER_ALPHA_2 132 
#define  HIER_ALPHA_4 131 
#define  HIER_NONE 130 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
#define  TRANS_MODE_2K 129 
#define  TRANS_MODE_8K 128 
 int stub1 (int /*<<< orphan*/ ,struct as10x_tps*) ; 

__attribute__((used)) static int as102_fe_get_frontend(struct dvb_frontend *fe,
				 struct dtv_frontend_properties *c)
{
	struct as102_state *state = fe->demodulator_priv;
	int ret = 0;
	struct as10x_tps tps = { 0 };

	/* send abilis command: GET_TPS */
	ret = state->ops->get_tps(state->priv, &tps);
	if (ret < 0)
		return ret;

	/* extract constellation */
	switch (tps.modulation) {
	case CONST_QPSK:
		c->modulation = QPSK;
		break;
	case CONST_QAM16:
		c->modulation = QAM_16;
		break;
	case CONST_QAM64:
		c->modulation = QAM_64;
		break;
	}

	/* extract hierarchy */
	switch (tps.hierarchy) {
	case HIER_NONE:
		c->hierarchy = HIERARCHY_NONE;
		break;
	case HIER_ALPHA_1:
		c->hierarchy = HIERARCHY_1;
		break;
	case HIER_ALPHA_2:
		c->hierarchy = HIERARCHY_2;
		break;
	case HIER_ALPHA_4:
		c->hierarchy = HIERARCHY_4;
		break;
	}

	/* extract code rate HP */
	switch (tps.code_rate_HP) {
	case CODE_RATE_1_2:
		c->code_rate_HP = FEC_1_2;
		break;
	case CODE_RATE_2_3:
		c->code_rate_HP = FEC_2_3;
		break;
	case CODE_RATE_3_4:
		c->code_rate_HP = FEC_3_4;
		break;
	case CODE_RATE_5_6:
		c->code_rate_HP = FEC_5_6;
		break;
	case CODE_RATE_7_8:
		c->code_rate_HP = FEC_7_8;
		break;
	}

	/* extract code rate LP */
	switch (tps.code_rate_LP) {
	case CODE_RATE_1_2:
		c->code_rate_LP = FEC_1_2;
		break;
	case CODE_RATE_2_3:
		c->code_rate_LP = FEC_2_3;
		break;
	case CODE_RATE_3_4:
		c->code_rate_LP = FEC_3_4;
		break;
	case CODE_RATE_5_6:
		c->code_rate_LP = FEC_5_6;
		break;
	case CODE_RATE_7_8:
		c->code_rate_LP = FEC_7_8;
		break;
	}

	/* extract guard interval */
	switch (tps.guard_interval) {
	case GUARD_INT_1_32:
		c->guard_interval = GUARD_INTERVAL_1_32;
		break;
	case GUARD_INT_1_16:
		c->guard_interval = GUARD_INTERVAL_1_16;
		break;
	case GUARD_INT_1_8:
		c->guard_interval = GUARD_INTERVAL_1_8;
		break;
	case GUARD_INT_1_4:
		c->guard_interval = GUARD_INTERVAL_1_4;
		break;
	}

	/* extract transmission mode */
	switch (tps.transmission_mode) {
	case TRANS_MODE_2K:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case TRANS_MODE_8K:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		break;
	}

	return 0;
}