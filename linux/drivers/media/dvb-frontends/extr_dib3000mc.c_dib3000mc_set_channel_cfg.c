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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct dtv_frontend_properties {int transmission_mode; int guard_interval; int modulation; int hierarchy; int code_rate_HP; int code_rate_LP; int /*<<< orphan*/  bandwidth_hz; } ;
struct dib3000mc_state {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  impulse_noise_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
#define  FEC_1_2 144 
#define  FEC_2_3 143 
#define  FEC_3_4 142 
#define  FEC_5_6 141 
#define  FEC_7_8 140 
#define  GUARD_INTERVAL_1_16 139 
#define  GUARD_INTERVAL_1_32 138 
#define  GUARD_INTERVAL_1_4 137 
#define  GUARD_INTERVAL_1_8 136 
#define  HIERARCHY_1 135 
#define  HIERARCHY_2 134 
#define  HIERARCHY_4 133 
#define  QAM_16 132 
#define  QAM_64 131 
#define  QPSK 130 
#define  TRANSMISSION_MODE_2K 129 
#define  TRANSMISSION_MODE_8K 128 
 scalar_t__ boost ; 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_set_adp_cfg (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_set_bandwidth (struct dib3000mc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_set_impulse_noise (struct dib3000mc_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib3000mc_set_timing (struct dib3000mc_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void dib3000mc_set_channel_cfg(struct dib3000mc_state *state,
				      struct dtv_frontend_properties *ch, u16 seq)
{
	u16 value;
	u32 bw = BANDWIDTH_TO_KHZ(ch->bandwidth_hz);

	dib3000mc_set_bandwidth(state, bw);
	dib3000mc_set_timing(state, ch->transmission_mode, bw, 0);

#if 1
	dib3000mc_write_word(state, 100, (16 << 6) + 9);
#else
	if (boost)
		dib3000mc_write_word(state, 100, (11 << 6) + 6);
	else
		dib3000mc_write_word(state, 100, (16 << 6) + 9);
#endif

	dib3000mc_write_word(state, 1027, 0x0800);
	dib3000mc_write_word(state, 1027, 0x0000);

	//Default cfg isi offset adp
	dib3000mc_write_word(state, 26,  0x6680);
	dib3000mc_write_word(state, 29,  0x1273);
	dib3000mc_write_word(state, 33,       5);
	dib3000mc_set_adp_cfg(state, QAM_16);
	dib3000mc_write_word(state, 133,  15564);

	dib3000mc_write_word(state, 12 , 0x0);
	dib3000mc_write_word(state, 13 , 0x3e8);
	dib3000mc_write_word(state, 14 , 0x0);
	dib3000mc_write_word(state, 15 , 0x3f2);

	dib3000mc_write_word(state, 93,0);
	dib3000mc_write_word(state, 94,0);
	dib3000mc_write_word(state, 95,0);
	dib3000mc_write_word(state, 96,0);
	dib3000mc_write_word(state, 97,0);
	dib3000mc_write_word(state, 98,0);

	dib3000mc_set_impulse_noise(state, 0, ch->transmission_mode);

	value = 0;
	switch (ch->transmission_mode) {
		case TRANSMISSION_MODE_2K: value |= (0 << 7); break;
		default:
		case TRANSMISSION_MODE_8K: value |= (1 << 7); break;
	}
	switch (ch->guard_interval) {
		case GUARD_INTERVAL_1_32: value |= (0 << 5); break;
		case GUARD_INTERVAL_1_16: value |= (1 << 5); break;
		case GUARD_INTERVAL_1_4:  value |= (3 << 5); break;
		default:
		case GUARD_INTERVAL_1_8:  value |= (2 << 5); break;
	}
	switch (ch->modulation) {
		case QPSK:  value |= (0 << 3); break;
		case QAM_16: value |= (1 << 3); break;
		default:
		case QAM_64: value |= (2 << 3); break;
	}
	switch (HIERARCHY_1) {
		case HIERARCHY_2: value |= 2; break;
		case HIERARCHY_4: value |= 4; break;
		default:
		case HIERARCHY_1: value |= 1; break;
	}
	dib3000mc_write_word(state, 0, value);
	dib3000mc_write_word(state, 5, (1 << 8) | ((seq & 0xf) << 4));

	value = 0;
	if (ch->hierarchy == 1)
		value |= (1 << 4);
	if (1 == 1)
		value |= 1;
	switch ((ch->hierarchy == 0 || 1 == 1) ? ch->code_rate_HP : ch->code_rate_LP) {
		case FEC_2_3: value |= (2 << 1); break;
		case FEC_3_4: value |= (3 << 1); break;
		case FEC_5_6: value |= (5 << 1); break;
		case FEC_7_8: value |= (7 << 1); break;
		default:
		case FEC_1_2: value |= (1 << 1); break;
	}
	dib3000mc_write_word(state, 181, value);

	// diversity synchro delay add 50% SFN margin
	switch (ch->transmission_mode) {
		case TRANSMISSION_MODE_8K: value = 256; break;
		case TRANSMISSION_MODE_2K:
		default: value = 64; break;
	}
	switch (ch->guard_interval) {
		case GUARD_INTERVAL_1_16: value *= 2; break;
		case GUARD_INTERVAL_1_8:  value *= 4; break;
		case GUARD_INTERVAL_1_4:  value *= 8; break;
		default:
		case GUARD_INTERVAL_1_32: value *= 1; break;
	}
	value <<= 4;
	value |= dib3000mc_read_word(state, 180) & 0x000f;
	dib3000mc_write_word(state, 180, value);

	// restart demod
	value = dib3000mc_read_word(state, 0);
	dib3000mc_write_word(state, 0, value | (1 << 9));
	dib3000mc_write_word(state, 0, value);

	msleep(30);

	dib3000mc_set_impulse_noise(state, state->cfg->impulse_noise_mode, ch->transmission_mode);
}