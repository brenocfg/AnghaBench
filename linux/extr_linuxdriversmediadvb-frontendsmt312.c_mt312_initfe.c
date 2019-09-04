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
struct mt312_state {int freq_mult; int id; int xtal; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  buf_def ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  CS_SW_LIM ; 
 int /*<<< orphan*/  GPP_CTRL ; 
 int /*<<< orphan*/  HW_CTRL ; 
#define  ID_ZL10313 128 
 int /*<<< orphan*/  MPEG_CTRL ; 
 int /*<<< orphan*/  OP_CTRL ; 
 int /*<<< orphan*/  SNR_THS_HIGH ; 
 int /*<<< orphan*/  SYS_CLK ; 
 int /*<<< orphan*/  TS_SW_LIM_L ; 
 int /*<<< orphan*/  VIT_SETUP ; 
 int mt312_div (int,int) ; 
 int mt312_reset (struct mt312_state*,int) ; 
 int mt312_write (struct mt312_state*,int /*<<< orphan*/ ,int*,int) ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt312_initfe(struct dvb_frontend *fe)
{
	struct mt312_state *state = fe->demodulator_priv;
	int ret;
	u8 buf[2];

	/* wake up */
	ret = mt312_writereg(state, CONFIG,
			(state->freq_mult == 6 ? 0x88 : 0x8c));
	if (ret < 0)
		return ret;

	/* wait at least 150 usec */
	udelay(150);

	/* full reset */
	ret = mt312_reset(state, 1);
	if (ret < 0)
		return ret;

/* Per datasheet, write correct values. 09/28/03 ACCJr.
 * If we don't do this, we won't get FE_HAS_VITERBI in the VP310. */
	{
		u8 buf_def[8] = { 0x14, 0x12, 0x03, 0x02,
				  0x01, 0x00, 0x00, 0x00 };

		ret = mt312_write(state, VIT_SETUP, buf_def, sizeof(buf_def));
		if (ret < 0)
			return ret;
	}

	switch (state->id) {
	case ID_ZL10313:
		/* enable ADC */
		ret = mt312_writereg(state, GPP_CTRL, 0x80);
		if (ret < 0)
			return ret;

		/* configure ZL10313 for optimal ADC performance */
		buf[0] = 0x80;
		buf[1] = 0xB0;
		ret = mt312_write(state, HW_CTRL, buf, 2);
		if (ret < 0)
			return ret;

		/* enable MPEG output and ADCs */
		ret = mt312_writereg(state, HW_CTRL, 0x00);
		if (ret < 0)
			return ret;

		ret = mt312_writereg(state, MPEG_CTRL, 0x00);
		if (ret < 0)
			return ret;

		break;
	}

	/* SYS_CLK */
	buf[0] = mt312_div(state->xtal * state->freq_mult * 2, 1000000);

	/* DISEQC_RATIO */
	buf[1] = mt312_div(state->xtal, 22000 * 4);

	ret = mt312_write(state, SYS_CLK, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	ret = mt312_writereg(state, SNR_THS_HIGH, 0x32);
	if (ret < 0)
		return ret;

	/* different MOCLK polarity */
	switch (state->id) {
	case ID_ZL10313:
		buf[0] = 0x33;
		break;
	default:
		buf[0] = 0x53;
		break;
	}

	ret = mt312_writereg(state, OP_CTRL, buf[0]);
	if (ret < 0)
		return ret;

	/* TS_SW_LIM */
	buf[0] = 0x8c;
	buf[1] = 0x98;

	ret = mt312_write(state, TS_SW_LIM_L, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	ret = mt312_writereg(state, CS_SW_LIM, 0x69);
	if (ret < 0)
		return ret;

	return 0;
}