#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct si2165_state {TYPE_3__* client; scalar_t__ ber_prev; } ;
struct TYPE_14__ {TYPE_6__* stat; } ;
struct TYPE_12__ {TYPE_4__* stat; } ;
struct TYPE_9__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {int delivery_system; TYPE_7__ post_bit_count; TYPE_5__ post_bit_error; TYPE_2__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct si2165_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_13__ {void* scale; scalar_t__ uvalue; } ;
struct TYPE_11__ {scalar_t__ scale; int uvalue; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int svalue; scalar_t__ scale; } ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 scalar_t__ FE_SCALE_DECIBEL ; 
 scalar_t__ FE_SCALE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  REG_BER_AVAIL ; 
 int /*<<< orphan*/  REG_BER_BIT ; 
 int /*<<< orphan*/  REG_BER_RST ; 
 int /*<<< orphan*/  REG_CHECK_SIGNAL ; 
 int /*<<< orphan*/  REG_C_N ; 
 int /*<<< orphan*/  REG_FEC_LOCK ; 
 int /*<<< orphan*/  REG_PS_LOCK ; 
 scalar_t__ STATISTICS_PERIOD_BIT_COUNT ; 
#define  SYS_DVBC_ANNEX_A 129 
#define  SYS_DVBT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 scalar_t__ intlog10 (int) ; 
 int si2165_readreg24 (struct si2165_state*,int /*<<< orphan*/ ,int*) ; 
 int si2165_readreg8 (struct si2165_state*,int /*<<< orphan*/ ,int*) ; 
 int si2165_writereg8 (struct si2165_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si2165_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	int ret;
	u8 u8tmp;
	u32 u32tmp;
	struct si2165_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_system;

	*status = 0;

	switch (delsys) {
	case SYS_DVBT:
		/* check fast signal type */
		ret = si2165_readreg8(state, REG_CHECK_SIGNAL, &u8tmp);
		if (ret < 0)
			return ret;
		switch (u8tmp & 0x3) {
		case 0: /* searching */
		case 1: /* nothing */
			break;
		case 2: /* digital signal */
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;
			break;
		}
		break;
	case SYS_DVBC_ANNEX_A:
		/* check packet sync lock */
		ret = si2165_readreg8(state, REG_PS_LOCK, &u8tmp);
		if (ret < 0)
			return ret;
		if (u8tmp & 0x01) {
			*status |= FE_HAS_SIGNAL;
			*status |= FE_HAS_CARRIER;
			*status |= FE_HAS_VITERBI;
			*status |= FE_HAS_SYNC;
		}
		break;
	}

	/* check fec_lock */
	ret = si2165_readreg8(state, REG_FEC_LOCK, &u8tmp);
	if (ret < 0)
		return ret;
	if (u8tmp & 0x01) {
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	}

	/* CNR */
	if (delsys == SYS_DVBC_ANNEX_A && *status & FE_HAS_VITERBI) {
		ret = si2165_readreg24(state, REG_C_N, &u32tmp);
		if (ret < 0)
			return ret;
		/*
		 * svalue =
		 * 1000 * c_n/dB =
		 * 1000 * 10 * log10(2^24 / regval) =
		 * 1000 * 10 * (log10(2^24) - log10(regval)) =
		 * 1000 * 10 * (intlog10(2^24) - intlog10(regval)) / 2^24
		 *
		 * intlog10(x) = log10(x) * 2^24
		 * intlog10(2^24) = log10(2^24) * 2^24 = 121210686
		 */
		u32tmp = (1000 * 10 * (121210686 - (u64)intlog10(u32tmp)))
				>> 24;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = u32tmp;
	} else
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* BER */
	if (*status & FE_HAS_VITERBI) {
		if (c->post_bit_error.stat[0].scale == FE_SCALE_NOT_AVAILABLE) {
			/* start new sampling period to get rid of old data*/
			ret = si2165_writereg8(state, REG_BER_RST, 0x01);
			if (ret < 0)
				return ret;

			/* set scale to enter read code on next call */
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = 0;
			c->post_bit_count.stat[0].uvalue = 0;

			/*
			 * reset DVBv3 value to deliver a good result
			 * for the first call
			 */
			state->ber_prev = 0;

		} else {
			ret = si2165_readreg8(state, REG_BER_AVAIL, &u8tmp);
			if (ret < 0)
				return ret;

			if (u8tmp & 1) {
				u32 biterrcnt;

				ret = si2165_readreg24(state, REG_BER_BIT,
							&biterrcnt);
				if (ret < 0)
					return ret;

				c->post_bit_error.stat[0].uvalue +=
					biterrcnt;
				c->post_bit_count.stat[0].uvalue +=
					STATISTICS_PERIOD_BIT_COUNT;

				/* start new sampling period */
				ret = si2165_writereg8(state,
							REG_BER_RST, 0x01);
				if (ret < 0)
					return ret;

				dev_dbg(&state->client->dev,
					"post_bit_error=%u post_bit_count=%u\n",
					biterrcnt, STATISTICS_PERIOD_BIT_COUNT);
			}
		}
	} else {
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return 0;
}