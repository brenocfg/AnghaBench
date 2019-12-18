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
typedef  int u16 ;
struct dtv_frontend_properties {int transmission_mode; int frequency; int /*<<< orphan*/  bandwidth_hz; } ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_2__ {scalar_t__ spur_protect; } ;
struct dib7000p_state {scalar_t__ timf; TYPE_1__ cfg; scalar_t__ sfn_workaround_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_reset_stats (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib7000p_set_bandwidth (struct dib7000p_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_set_channel (struct dib7000p_state*,struct dtv_frontend_properties*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_spur_protect (struct dib7000p_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_update_timf (struct dib7000p_state*) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib7000p_tune(struct dvb_frontend *demod)
{
	struct dtv_frontend_properties *ch = &demod->dtv_property_cache;
	struct dib7000p_state *state = demod->demodulator_priv;
	u16 tmp = 0;

	if (ch != NULL)
		dib7000p_set_channel(state, ch, 0);
	else
		return -EINVAL;

	// restart demod
	dib7000p_write_word(state, 770, 0x4000);
	dib7000p_write_word(state, 770, 0x0000);
	msleep(45);

	/* P_ctrl_inh_cor=0, P_ctrl_alpha_cor=4, P_ctrl_inh_isi=0, P_ctrl_alpha_isi=3, P_ctrl_inh_cor4=1, P_ctrl_alpha_cor4=3 */
	tmp = (0 << 14) | (4 << 10) | (0 << 9) | (3 << 5) | (1 << 4) | (0x3);
	if (state->sfn_workaround_active) {
		dprintk("SFN workaround is active\n");
		tmp |= (1 << 9);
		dib7000p_write_word(state, 166, 0x4000);
	} else {
		dib7000p_write_word(state, 166, 0x0000);
	}
	dib7000p_write_word(state, 29, tmp);

	// never achieved a lock with that bandwidth so far - wait for osc-freq to update
	if (state->timf == 0)
		msleep(200);

	/* offset loop parameters */

	/* P_timf_alpha, P_corm_alpha=6, P_corm_thres=0x80 */
	tmp = (6 << 8) | 0x80;
	switch (ch->transmission_mode) {
	case TRANSMISSION_MODE_2K:
		tmp |= (2 << 12);
		break;
	case TRANSMISSION_MODE_4K:
		tmp |= (3 << 12);
		break;
	default:
	case TRANSMISSION_MODE_8K:
		tmp |= (4 << 12);
		break;
	}
	dib7000p_write_word(state, 26, tmp);	/* timf_a(6xxx) */

	/* P_ctrl_freeze_pha_shift=0, P_ctrl_pha_off_max */
	tmp = (0 << 4);
	switch (ch->transmission_mode) {
	case TRANSMISSION_MODE_2K:
		tmp |= 0x6;
		break;
	case TRANSMISSION_MODE_4K:
		tmp |= 0x7;
		break;
	default:
	case TRANSMISSION_MODE_8K:
		tmp |= 0x8;
		break;
	}
	dib7000p_write_word(state, 32, tmp);

	/* P_ctrl_sfreq_inh=0, P_ctrl_sfreq_step */
	tmp = (0 << 4);
	switch (ch->transmission_mode) {
	case TRANSMISSION_MODE_2K:
		tmp |= 0x6;
		break;
	case TRANSMISSION_MODE_4K:
		tmp |= 0x7;
		break;
	default:
	case TRANSMISSION_MODE_8K:
		tmp |= 0x8;
		break;
	}
	dib7000p_write_word(state, 33, tmp);

	tmp = dib7000p_read_word(state, 509);
	if (!((tmp >> 6) & 0x1)) {
		/* restart the fec */
		tmp = dib7000p_read_word(state, 771);
		dib7000p_write_word(state, 771, tmp | (1 << 1));
		dib7000p_write_word(state, 771, tmp);
		msleep(40);
		tmp = dib7000p_read_word(state, 509);
	}
	// we achieved a lock - it's time to update the osc freq
	if ((tmp >> 6) & 0x1) {
		dib7000p_update_timf(state);
		/* P_timf_alpha += 2 */
		tmp = dib7000p_read_word(state, 26);
		dib7000p_write_word(state, 26, (tmp & ~(0xf << 12)) | ((((tmp >> 12) & 0xf) + 5) << 12));
	}

	if (state->cfg.spur_protect)
		dib7000p_spur_protect(state, ch->frequency / 1000, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	dib7000p_reset_stats(demod);

	return 0;
}