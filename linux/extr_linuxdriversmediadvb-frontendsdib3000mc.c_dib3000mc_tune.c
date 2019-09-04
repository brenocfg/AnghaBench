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
typedef  int /*<<< orphan*/  u8 ;
struct dtv_frontend_properties {scalar_t__ transmission_mode; int /*<<< orphan*/  bandwidth_hz; scalar_t__ modulation; } ;
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct dib3000mc_state {scalar_t__ sfn_workaround_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANSMISSION_MODE_8K ; 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_set_adp_cfg (struct dib3000mc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_set_channel_cfg (struct dib3000mc_state*,struct dtv_frontend_properties*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_set_timing (struct dib3000mc_state*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib3000mc_tune(struct dvb_frontend *demod)
{
	struct dtv_frontend_properties *ch = &demod->dtv_property_cache;
	struct dib3000mc_state *state = demod->demodulator_priv;

	// ** configure demod **
	dib3000mc_set_channel_cfg(state, ch, 0);

	// activates isi
	if (state->sfn_workaround_active) {
		dprintk("SFN workaround is active\n");
		dib3000mc_write_word(state, 29, 0x1273);
		dib3000mc_write_word(state, 108, 0x4000); // P_pha3_force_pha_shift
	} else {
		dib3000mc_write_word(state, 29, 0x1073);
		dib3000mc_write_word(state, 108, 0x0000); // P_pha3_force_pha_shift
	}

	dib3000mc_set_adp_cfg(state, (u8)ch->modulation);
	if (ch->transmission_mode == TRANSMISSION_MODE_8K) {
		dib3000mc_write_word(state, 26, 38528);
		dib3000mc_write_word(state, 33, 8);
	} else {
		dib3000mc_write_word(state, 26, 30336);
		dib3000mc_write_word(state, 33, 6);
	}

	if (dib3000mc_read_word(state, 509) & 0x80)
		dib3000mc_set_timing(state, ch->transmission_mode,
				     BANDWIDTH_TO_KHZ(ch->bandwidth_hz), 1);

	return 0;
}