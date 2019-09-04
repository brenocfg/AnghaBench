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
struct stv0297_state {int /*<<< orphan*/  base_freq; TYPE_1__* config; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_2__ tuner_ops; } ;
struct dtv_frontend_properties {int modulation; int inversion; int symbol_rate; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_3__ ops; struct stv0297_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  enum fe_spectral_inversion { ____Placeholder_fe_spectral_inversion } fe_spectral_inversion ;
struct TYPE_4__ {scalar_t__ invert; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_OFF 134 
#define  INVERSION_ON 133 
#define  QAM_128 132 
#define  QAM_16 131 
#define  QAM_256 130 
#define  QAM_32 129 
#define  QAM_64 128 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0297_init (struct dvb_frontend*) ; 
 int stv0297_readreg (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_set_carrieroffset (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_set_initialdemodfreq (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_set_inversion (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_set_qam (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_set_sweeprate (struct stv0297_state*,int,int) ; 
 int /*<<< orphan*/  stv0297_set_symbolrate (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,int) ; 
 int /*<<< orphan*/  stv0297_writereg_mask (struct stv0297_state*,int,int,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int stv0297_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct stv0297_state *state = fe->demodulator_priv;
	int u_threshold;
	int initial_u;
	int blind_u;
	int delay;
	int sweeprate;
	int carrieroffset;
	unsigned long timeout;
	enum fe_spectral_inversion inversion;

	switch (p->modulation) {
	case QAM_16:
	case QAM_32:
	case QAM_64:
		delay = 100;
		sweeprate = 1000;
		break;

	case QAM_128:
	case QAM_256:
		delay = 200;
		sweeprate = 500;
		break;

	default:
		return -EINVAL;
	}

	// determine inversion dependent parameters
	inversion = p->inversion;
	if (state->config->invert)
		inversion = (inversion == INVERSION_ON) ? INVERSION_OFF : INVERSION_ON;
	carrieroffset = -330;
	switch (inversion) {
	case INVERSION_OFF:
		break;

	case INVERSION_ON:
		sweeprate = -sweeprate;
		carrieroffset = -carrieroffset;
		break;

	default:
		return -EINVAL;
	}

	stv0297_init(fe);
	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	/* clear software interrupts */
	stv0297_writereg(state, 0x82, 0x0);

	/* set initial demodulation frequency */
	stv0297_set_initialdemodfreq(state, 7250);

	/* setup AGC */
	stv0297_writereg_mask(state, 0x43, 0x10, 0x00);
	stv0297_writereg(state, 0x41, 0x00);
	stv0297_writereg_mask(state, 0x42, 0x03, 0x01);
	stv0297_writereg_mask(state, 0x36, 0x60, 0x00);
	stv0297_writereg_mask(state, 0x36, 0x18, 0x00);
	stv0297_writereg_mask(state, 0x71, 0x80, 0x80);
	stv0297_writereg(state, 0x72, 0x00);
	stv0297_writereg(state, 0x73, 0x00);
	stv0297_writereg_mask(state, 0x74, 0x0F, 0x00);
	stv0297_writereg_mask(state, 0x43, 0x08, 0x00);
	stv0297_writereg_mask(state, 0x71, 0x80, 0x00);

	/* setup STL */
	stv0297_writereg_mask(state, 0x5a, 0x20, 0x20);
	stv0297_writereg_mask(state, 0x5b, 0x02, 0x02);
	stv0297_writereg_mask(state, 0x5b, 0x02, 0x00);
	stv0297_writereg_mask(state, 0x5b, 0x01, 0x00);
	stv0297_writereg_mask(state, 0x5a, 0x40, 0x40);

	/* disable frequency sweep */
	stv0297_writereg_mask(state, 0x6a, 0x01, 0x00);

	/* reset deinterleaver */
	stv0297_writereg_mask(state, 0x81, 0x01, 0x01);
	stv0297_writereg_mask(state, 0x81, 0x01, 0x00);

	/* ??? */
	stv0297_writereg_mask(state, 0x83, 0x20, 0x20);
	stv0297_writereg_mask(state, 0x83, 0x20, 0x00);

	/* reset equaliser */
	u_threshold = stv0297_readreg(state, 0x00) & 0xf;
	initial_u = stv0297_readreg(state, 0x01) >> 4;
	blind_u = stv0297_readreg(state, 0x01) & 0xf;
	stv0297_writereg_mask(state, 0x84, 0x01, 0x01);
	stv0297_writereg_mask(state, 0x84, 0x01, 0x00);
	stv0297_writereg_mask(state, 0x00, 0x0f, u_threshold);
	stv0297_writereg_mask(state, 0x01, 0xf0, initial_u << 4);
	stv0297_writereg_mask(state, 0x01, 0x0f, blind_u);

	/* data comes from internal A/D */
	stv0297_writereg_mask(state, 0x87, 0x80, 0x00);

	/* clear phase registers */
	stv0297_writereg(state, 0x63, 0x00);
	stv0297_writereg(state, 0x64, 0x00);
	stv0297_writereg(state, 0x65, 0x00);
	stv0297_writereg(state, 0x66, 0x00);
	stv0297_writereg(state, 0x67, 0x00);
	stv0297_writereg(state, 0x68, 0x00);
	stv0297_writereg_mask(state, 0x69, 0x0f, 0x00);

	/* set parameters */
	stv0297_set_qam(state, p->modulation);
	stv0297_set_symbolrate(state, p->symbol_rate / 1000);
	stv0297_set_sweeprate(state, sweeprate, p->symbol_rate / 1000);
	stv0297_set_carrieroffset(state, carrieroffset);
	stv0297_set_inversion(state, inversion);

	/* kick off lock */
	/* Disable corner detection for higher QAMs */
	if (p->modulation == QAM_128 ||
		p->modulation == QAM_256)
		stv0297_writereg_mask(state, 0x88, 0x08, 0x00);
	else
		stv0297_writereg_mask(state, 0x88, 0x08, 0x08);

	stv0297_writereg_mask(state, 0x5a, 0x20, 0x00);
	stv0297_writereg_mask(state, 0x6a, 0x01, 0x01);
	stv0297_writereg_mask(state, 0x43, 0x40, 0x40);
	stv0297_writereg_mask(state, 0x5b, 0x30, 0x00);
	stv0297_writereg_mask(state, 0x03, 0x0c, 0x0c);
	stv0297_writereg_mask(state, 0x03, 0x03, 0x03);
	stv0297_writereg_mask(state, 0x43, 0x10, 0x10);

	/* wait for WGAGC lock */
	timeout = jiffies + msecs_to_jiffies(2000);
	while (time_before(jiffies, timeout)) {
		msleep(10);
		if (stv0297_readreg(state, 0x43) & 0x08)
			break;
	}
	if (time_after(jiffies, timeout)) {
		goto timeout;
	}
	msleep(20);

	/* wait for equaliser partial convergence */
	timeout = jiffies + msecs_to_jiffies(500);
	while (time_before(jiffies, timeout)) {
		msleep(10);

		if (stv0297_readreg(state, 0x82) & 0x04) {
			break;
		}
	}
	if (time_after(jiffies, timeout)) {
		goto timeout;
	}

	/* wait for equaliser full convergence */
	timeout = jiffies + msecs_to_jiffies(delay);
	while (time_before(jiffies, timeout)) {
		msleep(10);

		if (stv0297_readreg(state, 0x82) & 0x08) {
			break;
		}
	}
	if (time_after(jiffies, timeout)) {
		goto timeout;
	}

	/* disable sweep */
	stv0297_writereg_mask(state, 0x6a, 1, 0);
	stv0297_writereg_mask(state, 0x88, 8, 0);

	/* wait for main lock */
	timeout = jiffies + msecs_to_jiffies(20);
	while (time_before(jiffies, timeout)) {
		msleep(10);

		if (stv0297_readreg(state, 0xDF) & 0x80) {
			break;
		}
	}
	if (time_after(jiffies, timeout)) {
		goto timeout;
	}
	msleep(100);

	/* is it still locked after that delay? */
	if (!(stv0297_readreg(state, 0xDF) & 0x80)) {
		goto timeout;
	}

	/* success!! */
	stv0297_writereg_mask(state, 0x5a, 0x40, 0x00);
	state->base_freq = p->frequency;
	return 0;

timeout:
	stv0297_writereg_mask(state, 0x6a, 0x01, 0x00);
	return 0;
}