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
typedef  int u64 ;
typedef  int u32 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dtv_frontend_properties {int guard_interval; int transmission_mode; TYPE_2__* layer; } ;
struct dib8000_state {TYPE_1__** fe; } ;
struct TYPE_4__ {int segment_count; int modulation; int fec; int interleaving; } ;
struct TYPE_3__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
#define  DQPSK 143 
#define  FEC_1_2 142 
#define  FEC_2_3 141 
#define  FEC_3_4 140 
#define  FEC_5_6 139 
#define  FEC_7_8 138 
#define  GUARD_INTERVAL_1_16 137 
#define  GUARD_INTERVAL_1_32 136 
#define  GUARD_INTERVAL_1_4 135 
#define  GUARD_INTERVAL_1_8 134 
#define  QAM_16 133 
#define  QAM_64 132 
#define  QPSK 131 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u32 dib8000_get_time_us(struct dvb_frontend *fe, int layer)
{
	struct dib8000_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	int ini_layer, end_layer, i;
	u64 time_us, tmp64;
	u32 tmp, denom;
	int guard, rate_num, rate_denum = 1, bits_per_symbol, nsegs;
	int interleaving = 0, fft_div;

	if (layer >= 0) {
		ini_layer = layer;
		end_layer = layer + 1;
	} else {
		ini_layer = 0;
		end_layer = 3;
	}

	switch (c->guard_interval) {
	case GUARD_INTERVAL_1_4:
		guard = 4;
		break;
	case GUARD_INTERVAL_1_8:
		guard = 8;
		break;
	case GUARD_INTERVAL_1_16:
		guard = 16;
		break;
	default:
	case GUARD_INTERVAL_1_32:
		guard = 32;
		break;
	}

	switch (c->transmission_mode) {
	case TRANSMISSION_MODE_2K:
		fft_div = 4;
		break;
	case TRANSMISSION_MODE_4K:
		fft_div = 2;
		break;
	default:
	case TRANSMISSION_MODE_8K:
		fft_div = 1;
		break;
	}

	denom = 0;
	for (i = ini_layer; i < end_layer; i++) {
		nsegs = c->layer[i].segment_count;
		if (nsegs == 0 || nsegs > 13)
			continue;

		switch (c->layer[i].modulation) {
		case DQPSK:
		case QPSK:
			bits_per_symbol = 2;
			break;
		case QAM_16:
			bits_per_symbol = 4;
			break;
		default:
		case QAM_64:
			bits_per_symbol = 6;
			break;
		}

		switch (c->layer[i].fec) {
		case FEC_1_2:
			rate_num = 1;
			rate_denum = 2;
			break;
		case FEC_2_3:
			rate_num = 2;
			rate_denum = 3;
			break;
		case FEC_3_4:
			rate_num = 3;
			rate_denum = 4;
			break;
		case FEC_5_6:
			rate_num = 5;
			rate_denum = 6;
			break;
		default:
		case FEC_7_8:
			rate_num = 7;
			rate_denum = 8;
			break;
		}

		interleaving = c->layer[i].interleaving;

		denom += bits_per_symbol * rate_num * fft_div * nsegs * 384;
	}

	/* If all goes wrong, wait for 1s for the next stats */
	if (!denom)
		return 0;

	/* Estimate the period for the total bit rate */
	time_us = rate_denum * (1008 * 1562500L);
	tmp64 = time_us;
	do_div(tmp64, guard);
	time_us = time_us + tmp64;
	time_us += denom / 2;
	do_div(time_us, denom);

	tmp = 1008 * 96 * interleaving;
	time_us += tmp + tmp / guard;

	return time_us;
}