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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {TYPE_2__** fe; } ;
typedef  int s8 ;
struct TYPE_3__ {int inversion; int transmission_mode; int guard_interval; int modulation; int hierarchy; int code_rate_HP; int code_rate_LP; } ;
struct TYPE_4__ {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
#define  FEC_1_2 154 
#define  FEC_2_3 153 
#define  FEC_3_4 152 
#define  FEC_5_6 151 
#define  FEC_7_8 150 
#define  FEC_AUTO 149 
 int /*<<< orphan*/  FE_MM_W_CHANNEL_UNION ; 
#define  GUARD_INTERVAL_1_16 148 
#define  GUARD_INTERVAL_1_32 147 
#define  GUARD_INTERVAL_1_4 146 
#define  GUARD_INTERVAL_1_8 145 
#define  GUARD_INTERVAL_AUTO 144 
#define  HIERARCHY_1 143 
#define  HIERARCHY_2 142 
#define  HIERARCHY_4 141 
#define  HIERARCHY_AUTO 140 
#define  HIERARCHY_NONE 139 
#define  INVERSION_AUTO 138 
#define  INVERSION_OFF 137 
#define  INVERSION_ON 136 
#define  QAM_16 135 
#define  QAM_64 134 
#define  QAM_AUTO 133 
#define  QPSK 132 
#define  TRANSMISSION_MODE_2K 131 
#define  TRANSMISSION_MODE_4K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 
 int /*<<< orphan*/  dib9000_risc_mem_write (struct dib9000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib9000_fw_set_channel_union(struct dvb_frontend *fe)
{
	struct dib9000_state *state = fe->demodulator_priv;
	struct dibDVBTChannel {
		s8 spectrum_inversion;

		s8 nfft;
		s8 guard;
		s8 constellation;

		s8 hrch;
		s8 alpha;
		s8 code_rate_hp;
		s8 code_rate_lp;
		s8 select_hp;

		s8 intlv_native;
	};
	struct dibDVBTChannel ch;

	switch (state->fe[0]->dtv_property_cache.inversion) {
	case INVERSION_ON:
		ch.spectrum_inversion = 1;
		break;
	case INVERSION_OFF:
		ch.spectrum_inversion = 0;
		break;
	default:
	case INVERSION_AUTO:
		ch.spectrum_inversion = -1;
		break;
	}
	switch (state->fe[0]->dtv_property_cache.transmission_mode) {
	case TRANSMISSION_MODE_2K:
		ch.nfft = 0;
		break;
	case TRANSMISSION_MODE_4K:
		ch.nfft = 2;
		break;
	case TRANSMISSION_MODE_8K:
		ch.nfft = 1;
		break;
	default:
	case TRANSMISSION_MODE_AUTO:
		ch.nfft = 1;
		break;
	}
	switch (state->fe[0]->dtv_property_cache.guard_interval) {
	case GUARD_INTERVAL_1_32:
		ch.guard = 0;
		break;
	case GUARD_INTERVAL_1_16:
		ch.guard = 1;
		break;
	case GUARD_INTERVAL_1_8:
		ch.guard = 2;
		break;
	case GUARD_INTERVAL_1_4:
		ch.guard = 3;
		break;
	default:
	case GUARD_INTERVAL_AUTO:
		ch.guard = -1;
		break;
	}
	switch (state->fe[0]->dtv_property_cache.modulation) {
	case QAM_64:
		ch.constellation = 2;
		break;
	case QAM_16:
		ch.constellation = 1;
		break;
	case QPSK:
		ch.constellation = 0;
		break;
	default:
	case QAM_AUTO:
		ch.constellation = -1;
		break;
	}
	switch (state->fe[0]->dtv_property_cache.hierarchy) {
	case HIERARCHY_NONE:
		ch.hrch = 0;
		break;
	case HIERARCHY_1:
	case HIERARCHY_2:
	case HIERARCHY_4:
		ch.hrch = 1;
		break;
	default:
	case HIERARCHY_AUTO:
		ch.hrch = -1;
		break;
	}
	ch.alpha = 1;
	switch (state->fe[0]->dtv_property_cache.code_rate_HP) {
	case FEC_1_2:
		ch.code_rate_hp = 1;
		break;
	case FEC_2_3:
		ch.code_rate_hp = 2;
		break;
	case FEC_3_4:
		ch.code_rate_hp = 3;
		break;
	case FEC_5_6:
		ch.code_rate_hp = 5;
		break;
	case FEC_7_8:
		ch.code_rate_hp = 7;
		break;
	default:
	case FEC_AUTO:
		ch.code_rate_hp = -1;
		break;
	}
	switch (state->fe[0]->dtv_property_cache.code_rate_LP) {
	case FEC_1_2:
		ch.code_rate_lp = 1;
		break;
	case FEC_2_3:
		ch.code_rate_lp = 2;
		break;
	case FEC_3_4:
		ch.code_rate_lp = 3;
		break;
	case FEC_5_6:
		ch.code_rate_lp = 5;
		break;
	case FEC_7_8:
		ch.code_rate_lp = 7;
		break;
	default:
	case FEC_AUTO:
		ch.code_rate_lp = -1;
		break;
	}
	ch.select_hp = 1;
	ch.intlv_native = 1;

	dib9000_risc_mem_write(state, FE_MM_W_CHANNEL_UNION, (u8 *) &ch);

	return 0;
}