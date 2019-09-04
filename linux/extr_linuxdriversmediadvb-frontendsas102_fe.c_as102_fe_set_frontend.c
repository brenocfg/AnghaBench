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
struct dtv_frontend_properties {int frequency; int bandwidth_hz; int guard_interval; int modulation; int transmission_mode; int hierarchy; scalar_t__ code_rate_LP; scalar_t__ code_rate_HP; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct as102_state* demodulator_priv; } ;
struct as10x_tune_args {int freq; scalar_t__ hier_select; void* code_rate; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  guard_interval; void* bandwidth; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  modulation; int /*<<< orphan*/  interleaving_mode; int /*<<< orphan*/  member_0; } ;
struct as102_state {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_tune ) (int /*<<< orphan*/ ,struct as10x_tune_args*) ;} ;

/* Variables and functions */
 void* BW_6_MHZ ; 
 void* BW_7_MHZ ; 
 void* BW_8_MHZ ; 
 int /*<<< orphan*/  CONST_QAM16 ; 
 int /*<<< orphan*/  CONST_QAM64 ; 
 int /*<<< orphan*/  CONST_QPSK ; 
 int /*<<< orphan*/  CONST_UNKNOWN ; 
 scalar_t__ FEC_NONE ; 
#define  GUARD_INTERVAL_1_16 142 
#define  GUARD_INTERVAL_1_32 141 
#define  GUARD_INTERVAL_1_4 140 
#define  GUARD_INTERVAL_1_8 139 
#define  GUARD_INTERVAL_AUTO 138 
 int /*<<< orphan*/  GUARD_INT_1_16 ; 
 int /*<<< orphan*/  GUARD_INT_1_32 ; 
 int /*<<< orphan*/  GUARD_INT_1_4 ; 
 int /*<<< orphan*/  GUARD_INT_1_8 ; 
 int /*<<< orphan*/  GUARD_UNKNOWN ; 
#define  HIERARCHY_1 137 
#define  HIERARCHY_2 136 
#define  HIERARCHY_4 135 
#define  HIERARCHY_AUTO 134 
#define  HIERARCHY_NONE 133 
 int /*<<< orphan*/  HIER_ALPHA_1 ; 
 int /*<<< orphan*/  HIER_ALPHA_2 ; 
 int /*<<< orphan*/  HIER_ALPHA_4 ; 
 scalar_t__ HIER_HIGH_PRIORITY ; 
 scalar_t__ HIER_LOW_PRIORITY ; 
 int /*<<< orphan*/  HIER_NONE ; 
 int /*<<< orphan*/  HIER_UNKNOWN ; 
 int /*<<< orphan*/  INTLV_NATIVE ; 
#define  QAM_16 132 
#define  QAM_64 131 
#define  QPSK 130 
#define  TRANSMISSION_MODE_2K 129 
#define  TRANSMISSION_MODE_8K 128 
 int /*<<< orphan*/  TRANS_MODE_2K ; 
 int /*<<< orphan*/  TRANS_MODE_8K ; 
 int /*<<< orphan*/  TRANS_MODE_UNKNOWN ; 
 void* as102_fe_get_code_rate (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,char*,...) ; 
 int stub1 (int /*<<< orphan*/ ,struct as10x_tune_args*) ; 

__attribute__((used)) static int as102_fe_set_frontend(struct dvb_frontend *fe)
{
	struct as102_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct as10x_tune_args tune_args = { 0 };

	/* set frequency */
	tune_args.freq = c->frequency / 1000;

	/* fix interleaving_mode */
	tune_args.interleaving_mode = INTLV_NATIVE;

	switch (c->bandwidth_hz) {
	case 8000000:
		tune_args.bandwidth = BW_8_MHZ;
		break;
	case 7000000:
		tune_args.bandwidth = BW_7_MHZ;
		break;
	case 6000000:
		tune_args.bandwidth = BW_6_MHZ;
		break;
	default:
		tune_args.bandwidth = BW_8_MHZ;
	}

	switch (c->guard_interval) {
	case GUARD_INTERVAL_1_32:
		tune_args.guard_interval = GUARD_INT_1_32;
		break;
	case GUARD_INTERVAL_1_16:
		tune_args.guard_interval = GUARD_INT_1_16;
		break;
	case GUARD_INTERVAL_1_8:
		tune_args.guard_interval = GUARD_INT_1_8;
		break;
	case GUARD_INTERVAL_1_4:
		tune_args.guard_interval = GUARD_INT_1_4;
		break;
	case GUARD_INTERVAL_AUTO:
	default:
		tune_args.guard_interval = GUARD_UNKNOWN;
		break;
	}

	switch (c->modulation) {
	case QPSK:
		tune_args.modulation = CONST_QPSK;
		break;
	case QAM_16:
		tune_args.modulation = CONST_QAM16;
		break;
	case QAM_64:
		tune_args.modulation = CONST_QAM64;
		break;
	default:
		tune_args.modulation = CONST_UNKNOWN;
		break;
	}

	switch (c->transmission_mode) {
	case TRANSMISSION_MODE_2K:
		tune_args.transmission_mode = TRANS_MODE_2K;
		break;
	case TRANSMISSION_MODE_8K:
		tune_args.transmission_mode = TRANS_MODE_8K;
		break;
	default:
		tune_args.transmission_mode = TRANS_MODE_UNKNOWN;
	}

	switch (c->hierarchy) {
	case HIERARCHY_NONE:
		tune_args.hierarchy = HIER_NONE;
		break;
	case HIERARCHY_1:
		tune_args.hierarchy = HIER_ALPHA_1;
		break;
	case HIERARCHY_2:
		tune_args.hierarchy = HIER_ALPHA_2;
		break;
	case HIERARCHY_4:
		tune_args.hierarchy = HIER_ALPHA_4;
		break;
	case HIERARCHY_AUTO:
		tune_args.hierarchy = HIER_UNKNOWN;
		break;
	}

	pr_debug("as102: tuner parameters: freq: %d  bw: 0x%02x  gi: 0x%02x\n",
			c->frequency,
			tune_args.bandwidth,
			tune_args.guard_interval);

	/*
	 * Detect a hierarchy selection
	 * if HP/LP are both set to FEC_NONE, HP will be selected.
	 */
	if ((tune_args.hierarchy != HIER_NONE) &&
		       ((c->code_rate_LP == FEC_NONE) ||
			(c->code_rate_HP == FEC_NONE))) {

		if (c->code_rate_LP == FEC_NONE) {
			tune_args.hier_select = HIER_HIGH_PRIORITY;
			tune_args.code_rate =
			   as102_fe_get_code_rate(c->code_rate_HP);
		}

		if (c->code_rate_HP == FEC_NONE) {
			tune_args.hier_select = HIER_LOW_PRIORITY;
			tune_args.code_rate =
			   as102_fe_get_code_rate(c->code_rate_LP);
		}

		pr_debug("as102: \thierarchy: 0x%02x  selected: %s  code_rate_%s: 0x%02x\n",
			tune_args.hierarchy,
			tune_args.hier_select == HIER_HIGH_PRIORITY ?
			"HP" : "LP",
			tune_args.hier_select == HIER_HIGH_PRIORITY ?
			"HP" : "LP",
			tune_args.code_rate);
	} else {
		tune_args.code_rate =
			as102_fe_get_code_rate(c->code_rate_HP);
	}

	/* Set frontend arguments */
	return state->ops->set_tune(state->priv, &tune_args);
}