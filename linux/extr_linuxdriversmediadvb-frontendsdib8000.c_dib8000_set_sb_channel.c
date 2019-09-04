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
struct dtv_frontend_properties {scalar_t__ transmission_mode; int isdbt_partial_reception; } ;
struct dib8000_state {int seg_mask; int mode; int seg_diff_mask; TYPE_1__** fe; } ;
struct TYPE_2__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 scalar_t__ TRANSMISSION_MODE_2K ; 
 scalar_t__ TRANSMISSION_MODE_4K ; 
 int* coff_thres_1seg ; 
 int* coff_thres_3seg ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int const) ; 

__attribute__((used)) static void dib8000_set_sb_channel(struct dib8000_state *state)
{
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	const u16 *coff;
	u16 i;

	if (c->transmission_mode == TRANSMISSION_MODE_2K || c->transmission_mode == TRANSMISSION_MODE_4K) {
		dib8000_write_word(state, 219, dib8000_read_word(state, 219) | 0x1); /* adp_pass =1 */
		dib8000_write_word(state, 190, dib8000_read_word(state, 190) | (0x1 << 14)); /* pha3_force_pha_shift = 1 */
	} else {
		dib8000_write_word(state, 219, dib8000_read_word(state, 219) & 0xfffe); /* adp_pass =0 */
		dib8000_write_word(state, 190, dib8000_read_word(state, 190) & 0xbfff); /* pha3_force_pha_shift = 0 */
	}

	if (c->isdbt_partial_reception == 1) /* 3-segments */
		state->seg_mask = 0x00E0;
	else /* 1-segment */
		state->seg_mask = 0x0040;

	dib8000_write_word(state, 268, (dib8000_read_word(state, 268) & 0xF9FF) | 0x0200);

	/* ---- COFF ---- Carloff, the most robust --- */
	/* P_coff_cpil_alpha=4, P_coff_inh=0, P_coff_cpil_winlen=64, P_coff_narrow_band=1, P_coff_square_val=1, P_coff_one_seg=~partial_rcpt, P_coff_use_tmcc=1, P_coff_use_ac=1 */
	dib8000_write_word(state, 187, (4 << 12) | (0 << 11) | (63 << 5) | (0x3 << 3) | ((~c->isdbt_partial_reception & 1) << 2) | 0x3);

	dib8000_write_word(state, 340, (16 << 6) | (8 << 0)); /* P_ctrl_pre_freq_win_len=16, P_ctrl_pre_freq_thres_lockin=8 */
	dib8000_write_word(state, 341, (6 << 3) | (1 << 2) | (1 << 1) | (1 << 0));/* P_ctrl_pre_freq_thres_lockout=6, P_small_use_tmcc/ac/cp=1 */

	/* Sound Broadcasting mode 1 seg */
	if (c->isdbt_partial_reception == 0) {
		/* P_coff_winlen=63, P_coff_thres_lock=15, P_coff_one_seg_width = (P_mode == 3) , P_coff_one_seg_sym = (P_mode-1) */
		if (state->mode == 3)
			dib8000_write_word(state, 180, 0x1fcf | ((state->mode - 1) << 14));
		else
			dib8000_write_word(state, 180, 0x0fcf | ((state->mode - 1) << 14));

		/* P_ctrl_corm_thres4pre_freq_inh=1,P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 5, P_pre_freq_win_len=4 */
		dib8000_write_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (5 << 5) | 4);
		coff = &coff_thres_1seg[0];
	} else {   /* Sound Broadcasting mode 3 seg */
		dib8000_write_word(state, 180, 0x1fcf | (1 << 14));
		/* P_ctrl_corm_thres4pre_freq_inh = 1, P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 4, P_pre_freq_win_len=4 */
		dib8000_write_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (4 << 5) | 4);
		coff = &coff_thres_3seg[0];
	}

	dib8000_write_word(state, 228, 1); /* P_2d_mode_byp=1 */
	dib8000_write_word(state, 205, dib8000_read_word(state, 205) & 0xfff0); /* P_cspu_win_cut = 0 */

	if (c->isdbt_partial_reception == 0 && c->transmission_mode == TRANSMISSION_MODE_2K)
		dib8000_write_word(state, 265, 15); /* P_equal_noise_sel = 15 */

	/* Write COFF thres */
	for (i = 0 ; i < 3; i++) {
		dib8000_write_word(state, 181+i, coff[i]);
		dib8000_write_word(state, 184+i, coff[i]);
	}

	/*
	 * make the cpil_coff_lock more robust but slower p_coff_winlen
	 * 6bits; p_coff_thres_lock 6bits (for coff lock if needed)
	 */

	dib8000_write_word(state, 266, ~state->seg_mask | state->seg_diff_mask); /* P_equal_noise_seg_inh */

	if (c->isdbt_partial_reception == 0)
		dib8000_write_word(state, 178, 64); /* P_fft_powrange = 64 */
	else
		dib8000_write_word(state, 178, 32); /* P_fft_powrange = 32 */
}