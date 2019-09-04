#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct l64781_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int bandwidth_hz; scalar_t__ inversion; scalar_t__ code_rate_HP; int hierarchy; scalar_t__ code_rate_LP; size_t modulation; int transmission_mode; size_t guard_interval; } ;
struct dvb_frontend {TYPE_2__ ops; struct l64781_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FEC_1_2 ; 
 scalar_t__ FEC_2_3 ; 
 scalar_t__ FEC_3_4 ; 
 scalar_t__ FEC_5_6 ; 
 scalar_t__ FEC_7_8 ; 
 int GUARD_INTERVAL_1_32 ; 
 size_t GUARD_INTERVAL_1_4 ; 
 int HIERARCHY_4 ; 
 int HIERARCHY_NONE ; 
 scalar_t__ INVERSION_OFF ; 
 scalar_t__ INVERSION_ON ; 
 size_t QAM_16 ; 
 size_t QAM_64 ; 
 size_t QPSK ; 
 int TRANSMISSION_MODE_2K ; 
 int TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  apply_tps (struct l64781_state*) ; 
 int /*<<< orphan*/  l64781_readreg (struct l64781_state*,int) ; 
 int /*<<< orphan*/  l64781_writereg (struct l64781_state*,int,int) ; 
 int /*<<< orphan*/  reset_afc (struct l64781_state*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_frontend_param(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct l64781_state* state = fe->demodulator_priv;
	/* The coderates for FEC_NONE, FEC_4_5 and FEC_FEC_6_7 are arbitrary */
	static const u8 fec_tab[] = { 7, 0, 1, 2, 9, 3, 10, 4 };
	/* QPSK, QAM_16, QAM_64 */
	static const u8 qam_tab [] = { 2, 4, 0, 6 };
	static const u8 guard_tab [] = { 1, 2, 4, 8 };
	/* The Grundig 29504-401.04 Tuner comes with 18.432MHz crystal. */
	static const u32 ppm = 8000;
	u32 ddfs_offset_fixed;
/*	u32 ddfs_offset_variable = 0x6000-((1000000UL+ppm)/ */
/*			bw_tab[p->bandWidth]<<10)/15625; */
	u32 init_freq;
	u32 spi_bias;
	u8 val0x04;
	u8 val0x05;
	u8 val0x06;
	int bw;

	switch (p->bandwidth_hz) {
	case 8000000:
		bw = 8;
		break;
	case 7000000:
		bw = 7;
		break;
	case 6000000:
		bw = 6;
		break;
	default:
		return -EINVAL;
	}

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	if (p->inversion != INVERSION_ON &&
	    p->inversion != INVERSION_OFF)
		return -EINVAL;

	if (p->code_rate_HP != FEC_1_2 && p->code_rate_HP != FEC_2_3 &&
	    p->code_rate_HP != FEC_3_4 && p->code_rate_HP != FEC_5_6 &&
	    p->code_rate_HP != FEC_7_8)
		return -EINVAL;

	if (p->hierarchy != HIERARCHY_NONE &&
	    (p->code_rate_LP != FEC_1_2 && p->code_rate_LP != FEC_2_3 &&
	     p->code_rate_LP != FEC_3_4 && p->code_rate_LP != FEC_5_6 &&
	     p->code_rate_LP != FEC_7_8))
		return -EINVAL;

	if (p->modulation != QPSK && p->modulation != QAM_16 &&
	    p->modulation != QAM_64)
		return -EINVAL;

	if (p->transmission_mode != TRANSMISSION_MODE_2K &&
	    p->transmission_mode != TRANSMISSION_MODE_8K)
		return -EINVAL;

	if ((int)p->guard_interval < GUARD_INTERVAL_1_32 ||
	    p->guard_interval > GUARD_INTERVAL_1_4)
		return -EINVAL;

	if ((int)p->hierarchy < HIERARCHY_NONE ||
	    p->hierarchy > HIERARCHY_4)
		return -EINVAL;

	ddfs_offset_fixed = 0x4000-(ppm<<16)/bw/1000000;

	/* This works up to 20000 ppm, it overflows if too large ppm! */
	init_freq = (((8UL<<25) + (8UL<<19) / 25*ppm / (15625/25)) /
			bw & 0xFFFFFF);

	/* SPI bias calculation is slightly modified to fit in 32bit */
	/* will work for high ppm only... */
	spi_bias = 378 * (1 << 10);
	spi_bias *= 16;
	spi_bias *= bw;
	spi_bias *= qam_tab[p->modulation];
	spi_bias /= p->code_rate_HP + 1;
	spi_bias /= (guard_tab[p->guard_interval] + 32);
	spi_bias *= 1000;
	spi_bias /= 1000 + ppm/1000;
	spi_bias *= p->code_rate_HP;

	val0x04 = (p->transmission_mode << 2) | p->guard_interval;
	val0x05 = fec_tab[p->code_rate_HP];

	if (p->hierarchy != HIERARCHY_NONE)
		val0x05 |= (p->code_rate_LP - FEC_1_2) << 3;

	val0x06 = (p->hierarchy << 2) | p->modulation;

	l64781_writereg (state, 0x04, val0x04);
	l64781_writereg (state, 0x05, val0x05);
	l64781_writereg (state, 0x06, val0x06);

	reset_afc (state);

	/* Technical manual section 2.6.1, TIM_IIR_GAIN optimal values */
	l64781_writereg (state, 0x15,
			 p->transmission_mode == TRANSMISSION_MODE_2K ? 1 : 3);
	l64781_writereg (state, 0x16, init_freq & 0xff);
	l64781_writereg (state, 0x17, (init_freq >> 8) & 0xff);
	l64781_writereg (state, 0x18, (init_freq >> 16) & 0xff);

	l64781_writereg (state, 0x1b, spi_bias & 0xff);
	l64781_writereg (state, 0x1c, (spi_bias >> 8) & 0xff);
	l64781_writereg (state, 0x1d, ((spi_bias >> 16) & 0x7f) |
		(p->inversion == INVERSION_ON ? 0x80 : 0x00));

	l64781_writereg (state, 0x22, ddfs_offset_fixed & 0xff);
	l64781_writereg (state, 0x23, (ddfs_offset_fixed >> 8) & 0x3f);

	l64781_readreg (state, 0x00);  /*  clear interrupt registers... */
	l64781_readreg (state, 0x01);  /*  dto. */

	apply_tps (state);

	return 0;
}