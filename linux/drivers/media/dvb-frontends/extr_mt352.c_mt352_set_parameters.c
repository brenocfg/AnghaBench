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
struct TYPE_4__ {scalar_t__ no_tuner; } ;
struct mt352_state {TYPE_1__ config; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* calc_regs ) (struct dvb_frontend*,unsigned char*,int) ;int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_6__ {TYPE_2__ tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;} ;
struct dtv_frontend_properties {int code_rate_HP; int code_rate_LP; int hierarchy; int modulation; int transmission_mode; int guard_interval; int /*<<< orphan*/  bandwidth_hz; } ;
struct dvb_frontend {TYPE_3__ ops; struct mt352_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
#define  FEC_1_2 151 
#define  FEC_2_3 150 
#define  FEC_3_4 149 
#define  FEC_5_6 148 
#define  FEC_7_8 147 
#define  FEC_AUTO 146 
#define  FEC_NONE 145 
#define  GUARD_INTERVAL_1_16 144 
#define  GUARD_INTERVAL_1_32 143 
#define  GUARD_INTERVAL_1_4 142 
#define  GUARD_INTERVAL_1_8 141 
#define  GUARD_INTERVAL_AUTO 140 
#define  HIERARCHY_1 139 
#define  HIERARCHY_2 138 
#define  HIERARCHY_4 137 
#define  HIERARCHY_AUTO 136 
#define  HIERARCHY_NONE 135 
#define  QAM_16 134 
#define  QAM_64 133 
#define  QAM_AUTO 132 
#define  QPSK 131 
 unsigned char TPS_GIVEN_1 ; 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 
 int /*<<< orphan*/  _mt352_write (struct dvb_frontend*,unsigned char*,int) ; 
 unsigned char lsb (unsigned int) ; 
 unsigned char msb (unsigned int) ; 
 int /*<<< orphan*/  mt352_calc_input_freq (struct mt352_state*,unsigned char*) ; 
 int /*<<< orphan*/  mt352_calc_nominal_rate (struct mt352_state*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,unsigned char*,int) ; 

__attribute__((used)) static int mt352_set_parameters(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *op = &fe->dtv_property_cache;
	struct mt352_state* state = fe->demodulator_priv;
	unsigned char buf[13];
	static unsigned char tuner_go[] = { 0x5d, 0x01 };
	static unsigned char fsm_go[]   = { 0x5e, 0x01 };
	unsigned int tps = 0;

	switch (op->code_rate_HP) {
		case FEC_2_3:
			tps |= (1 << 7);
			break;
		case FEC_3_4:
			tps |= (2 << 7);
			break;
		case FEC_5_6:
			tps |= (3 << 7);
			break;
		case FEC_7_8:
			tps |= (4 << 7);
			break;
		case FEC_1_2:
		case FEC_AUTO:
			break;
		default:
			return -EINVAL;
	}

	switch (op->code_rate_LP) {
		case FEC_2_3:
			tps |= (1 << 4);
			break;
		case FEC_3_4:
			tps |= (2 << 4);
			break;
		case FEC_5_6:
			tps |= (3 << 4);
			break;
		case FEC_7_8:
			tps |= (4 << 4);
			break;
		case FEC_1_2:
		case FEC_AUTO:
			break;
		case FEC_NONE:
			if (op->hierarchy == HIERARCHY_AUTO ||
			    op->hierarchy == HIERARCHY_NONE)
				break;
			/* fall through */
		default:
			return -EINVAL;
	}

	switch (op->modulation) {
		case QPSK:
			break;
		case QAM_AUTO:
		case QAM_16:
			tps |= (1 << 13);
			break;
		case QAM_64:
			tps |= (2 << 13);
			break;
		default:
			return -EINVAL;
	}

	switch (op->transmission_mode) {
		case TRANSMISSION_MODE_2K:
		case TRANSMISSION_MODE_AUTO:
			break;
		case TRANSMISSION_MODE_8K:
			tps |= (1 << 0);
			break;
		default:
			return -EINVAL;
	}

	switch (op->guard_interval) {
		case GUARD_INTERVAL_1_32:
		case GUARD_INTERVAL_AUTO:
			break;
		case GUARD_INTERVAL_1_16:
			tps |= (1 << 2);
			break;
		case GUARD_INTERVAL_1_8:
			tps |= (2 << 2);
			break;
		case GUARD_INTERVAL_1_4:
			tps |= (3 << 2);
			break;
		default:
			return -EINVAL;
	}

	switch (op->hierarchy) {
		case HIERARCHY_AUTO:
		case HIERARCHY_NONE:
			break;
		case HIERARCHY_1:
			tps |= (1 << 10);
			break;
		case HIERARCHY_2:
			tps |= (2 << 10);
			break;
		case HIERARCHY_4:
			tps |= (3 << 10);
			break;
		default:
			return -EINVAL;
	}


	buf[0] = TPS_GIVEN_1; /* TPS_GIVEN_1 and following registers */

	buf[1] = msb(tps);      /* TPS_GIVEN_(1|0) */
	buf[2] = lsb(tps);

	buf[3] = 0x50;  // old
//	buf[3] = 0xf4;  // pinnacle

	mt352_calc_nominal_rate(state, op->bandwidth_hz, buf+4);
	mt352_calc_input_freq(state, buf+6);

	if (state->config.no_tuner) {
		if (fe->ops.tuner_ops.set_params) {
			fe->ops.tuner_ops.set_params(fe);
			if (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		}

		_mt352_write(fe, buf, 8);
		_mt352_write(fe, fsm_go, 2);
	} else {
		if (fe->ops.tuner_ops.calc_regs) {
			fe->ops.tuner_ops.calc_regs(fe, buf+8, 5);
			buf[8] <<= 1;
			_mt352_write(fe, buf, sizeof(buf));
			_mt352_write(fe, tuner_go, 2);
		}
	}

	return 0;
}