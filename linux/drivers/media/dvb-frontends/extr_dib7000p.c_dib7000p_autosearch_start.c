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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dtv_frontend_properties {int /*<<< orphan*/  bandwidth_hz; scalar_t__ hierarchy; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  modulation; } ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct dib7000p_state {scalar_t__ version; } ;

/* Variables and functions */
 int BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 scalar_t__ SOC7090 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int dib7000p_get_internal_freq (struct dib7000p_state*) ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_set_channel (struct dib7000p_state*,struct dtv_frontend_properties*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib7000p_autosearch_start(struct dvb_frontend *demod)
{
	struct dtv_frontend_properties *ch = &demod->dtv_property_cache;
	struct dib7000p_state *state = demod->demodulator_priv;
	struct dtv_frontend_properties schan;
	u32 value, factor;
	u32 internal = dib7000p_get_internal_freq(state);

	schan = *ch;
	schan.modulation = QAM_64;
	schan.guard_interval = GUARD_INTERVAL_1_32;
	schan.transmission_mode = TRANSMISSION_MODE_8K;
	schan.code_rate_HP = FEC_2_3;
	schan.code_rate_LP = FEC_3_4;
	schan.hierarchy = 0;

	dib7000p_set_channel(state, &schan, 7);

	factor = BANDWIDTH_TO_KHZ(ch->bandwidth_hz);
	if (factor >= 5000) {
		if (state->version == SOC7090)
			factor = 2;
		else
			factor = 1;
	} else
		factor = 6;

	value = 30 * internal * factor;
	dib7000p_write_word(state, 6, (u16) ((value >> 16) & 0xffff));
	dib7000p_write_word(state, 7, (u16) (value & 0xffff));
	value = 100 * internal * factor;
	dib7000p_write_word(state, 8, (u16) ((value >> 16) & 0xffff));
	dib7000p_write_word(state, 9, (u16) (value & 0xffff));
	value = 500 * internal * factor;
	dib7000p_write_word(state, 10, (u16) ((value >> 16) & 0xffff));
	dib7000p_write_word(state, 11, (u16) (value & 0xffff));

	value = dib7000p_read_word(state, 0);
	dib7000p_write_word(state, 0, (u16) ((1 << 9) | value));
	dib7000p_read_word(state, 1284);
	dib7000p_write_word(state, 0, (u16) value);

	return 0;
}