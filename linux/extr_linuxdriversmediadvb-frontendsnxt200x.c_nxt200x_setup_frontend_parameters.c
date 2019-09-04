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
typedef  int u8 ;
struct nxt200x_state {int demod_chip; TYPE_1__* config; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* calc_regs ) (struct dvb_frontend*,int*,int) ;} ;
struct TYPE_6__ {TYPE_2__ tuner_ops; } ;
struct dtv_frontend_properties {int modulation; } ;
struct dvb_frontend {TYPE_3__ ops; struct nxt200x_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_ts_params ) (struct dvb_frontend*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  NXT2002 132 
#define  NXT2004 131 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  nxt2004_microcontroller_init (struct nxt200x_state*) ; 
 int /*<<< orphan*/  nxt200x_agc_reset (struct nxt200x_state*) ; 
 int /*<<< orphan*/  nxt200x_microcontroller_start (struct nxt200x_state*) ; 
 int /*<<< orphan*/  nxt200x_microcontroller_stop (struct nxt200x_state*) ; 
 int /*<<< orphan*/  nxt200x_readreg_multibyte (struct nxt200x_state*,int,int*,int) ; 
 int /*<<< orphan*/  nxt200x_writebytes (struct nxt200x_state*,int,int*,int) ; 
 int /*<<< orphan*/  nxt200x_writereg_multibyte (struct nxt200x_state*,int,int*,int) ; 
 int /*<<< orphan*/  nxt200x_writetuner (struct nxt200x_state*,int*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int*,int) ; 

__attribute__((used)) static int nxt200x_setup_frontend_parameters(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct nxt200x_state* state = fe->demodulator_priv;
	u8 buf[5];

	/* stop the micro first */
	nxt200x_microcontroller_stop(state);

	if (state->demod_chip == NXT2004) {
		/* make sure demod is set to digital */
		buf[0] = 0x04;
		nxt200x_writebytes(state, 0x14, buf, 1);
		buf[0] = 0x00;
		nxt200x_writebytes(state, 0x17, buf, 1);
	}

	/* set additional params */
	switch (p->modulation) {
		case QAM_64:
		case QAM_256:
			/* Set punctured clock for QAM */
			/* This is just a guess since I am unable to test it */
			if (state->config->set_ts_params)
				state->config->set_ts_params(fe, 1);
			break;
		case VSB_8:
			/* Set non-punctured clock for VSB */
			if (state->config->set_ts_params)
				state->config->set_ts_params(fe, 0);
			break;
		default:
			return -EINVAL;
			break;
	}

	if (fe->ops.tuner_ops.calc_regs) {
		/* get tuning information */
		fe->ops.tuner_ops.calc_regs(fe, buf, 5);

		/* write frequency information */
		nxt200x_writetuner(state, buf);
	}

	/* reset the agc now that tuning has been completed */
	nxt200x_agc_reset(state);

	/* set target power level */
	switch (p->modulation) {
		case QAM_64:
		case QAM_256:
			buf[0] = 0x74;
			break;
		case VSB_8:
			buf[0] = 0x70;
			break;
		default:
			return -EINVAL;
			break;
	}
	nxt200x_writebytes(state, 0x42, buf, 1);

	/* configure sdm */
	switch (state->demod_chip) {
		case NXT2002:
			buf[0] = 0x87;
			break;
		case NXT2004:
			buf[0] = 0x07;
			break;
		default:
			return -EINVAL;
			break;
	}
	nxt200x_writebytes(state, 0x57, buf, 1);

	/* write sdm1 input */
	buf[0] = 0x10;
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_writereg_multibyte(state, 0x58, buf, 2);
			break;
		case NXT2004:
			nxt200x_writebytes(state, 0x58, buf, 2);
			break;
		default:
			return -EINVAL;
			break;
	}

	/* write sdmx input */
	switch (p->modulation) {
		case QAM_64:
				buf[0] = 0x68;
				break;
		case QAM_256:
				buf[0] = 0x64;
				break;
		case VSB_8:
				buf[0] = 0x60;
				break;
		default:
				return -EINVAL;
				break;
	}
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_writereg_multibyte(state, 0x5C, buf, 2);
			break;
		case NXT2004:
			nxt200x_writebytes(state, 0x5C, buf, 2);
			break;
		default:
			return -EINVAL;
			break;
	}

	/* write adc power lpf fc */
	buf[0] = 0x05;
	nxt200x_writebytes(state, 0x43, buf, 1);

	if (state->demod_chip == NXT2004) {
		/* write ??? */
		buf[0] = 0x00;
		buf[1] = 0x00;
		nxt200x_writebytes(state, 0x46, buf, 2);
	}

	/* write accumulator2 input */
	buf[0] = 0x80;
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_writereg_multibyte(state, 0x4B, buf, 2);
			break;
		case NXT2004:
			nxt200x_writebytes(state, 0x4B, buf, 2);
			break;
		default:
			return -EINVAL;
			break;
	}

	/* write kg1 */
	buf[0] = 0x00;
	nxt200x_writebytes(state, 0x4D, buf, 1);

	/* write sdm12 lpf fc */
	buf[0] = 0x44;
	nxt200x_writebytes(state, 0x55, buf, 1);

	/* write agc control reg */
	buf[0] = 0x04;
	nxt200x_writebytes(state, 0x41, buf, 1);

	if (state->demod_chip == NXT2004) {
		nxt200x_readreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x24;
		nxt200x_writereg_multibyte(state, 0x80, buf, 1);

		/* soft reset? */
		nxt200x_readreg_multibyte(state, 0x08, buf, 1);
		buf[0] = 0x10;
		nxt200x_writereg_multibyte(state, 0x08, buf, 1);
		nxt200x_readreg_multibyte(state, 0x08, buf, 1);
		buf[0] = 0x00;
		nxt200x_writereg_multibyte(state, 0x08, buf, 1);

		nxt200x_readreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x04;
		nxt200x_writereg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x00;
		nxt200x_writereg_multibyte(state, 0x81, buf, 1);
		buf[0] = 0x80; buf[1] = 0x00; buf[2] = 0x00;
		nxt200x_writereg_multibyte(state, 0x82, buf, 3);
		nxt200x_readreg_multibyte(state, 0x88, buf, 1);
		buf[0] = 0x11;
		nxt200x_writereg_multibyte(state, 0x88, buf, 1);
		nxt200x_readreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x44;
		nxt200x_writereg_multibyte(state, 0x80, buf, 1);
	}

	/* write agc ucgp0 */
	switch (p->modulation) {
		case QAM_64:
				buf[0] = 0x02;
				break;
		case QAM_256:
				buf[0] = 0x03;
				break;
		case VSB_8:
				buf[0] = 0x00;
				break;
		default:
				return -EINVAL;
				break;
	}
	nxt200x_writebytes(state, 0x30, buf, 1);

	/* write agc control reg */
	buf[0] = 0x00;
	nxt200x_writebytes(state, 0x41, buf, 1);

	/* write accumulator2 input */
	buf[0] = 0x80;
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_writereg_multibyte(state, 0x49, buf, 2);
			nxt200x_writereg_multibyte(state, 0x4B, buf, 2);
			break;
		case NXT2004:
			nxt200x_writebytes(state, 0x49, buf, 2);
			nxt200x_writebytes(state, 0x4B, buf, 2);
			break;
		default:
			return -EINVAL;
			break;
	}

	/* write agc control reg */
	buf[0] = 0x04;
	nxt200x_writebytes(state, 0x41, buf, 1);

	nxt200x_microcontroller_start(state);

	if (state->demod_chip == NXT2004) {
		nxt2004_microcontroller_init(state);

		/* ???? */
		buf[0] = 0xF0;
		buf[1] = 0x00;
		nxt200x_writebytes(state, 0x5C, buf, 2);
	}

	/* adjacent channel detection should be done here, but I don't
	have any stations with this need so I cannot test it */

	return 0;
}