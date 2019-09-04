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
typedef  int u16 ;
struct dtv_frontend_properties {scalar_t__ hierarchy; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  modulation; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct dib3000mc_state {int dummy; } ;

/* Variables and functions */
 void* FEC_2_3 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_set_channel_cfg (struct dib3000mc_state*,struct dtv_frontend_properties*,int) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib3000mc_autosearch_start(struct dvb_frontend *demod)
{
	struct dtv_frontend_properties *chan = &demod->dtv_property_cache;
	struct dib3000mc_state *state = demod->demodulator_priv;
	u16 reg;
//	u32 val;
	struct dtv_frontend_properties schan;

	schan = *chan;

	/* TODO what is that ? */

	/* a channel for autosearch */
	schan.transmission_mode = TRANSMISSION_MODE_8K;
	schan.guard_interval = GUARD_INTERVAL_1_32;
	schan.modulation = QAM_64;
	schan.code_rate_HP = FEC_2_3;
	schan.code_rate_LP = FEC_2_3;
	schan.hierarchy = 0;

	dib3000mc_set_channel_cfg(state, &schan, 11);

	reg = dib3000mc_read_word(state, 0);
	dib3000mc_write_word(state, 0, reg | (1 << 8));
	dib3000mc_read_word(state, 511);
	dib3000mc_write_word(state, 0, reg);

	return 0;
}