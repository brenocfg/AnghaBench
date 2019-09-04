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
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* pll; } ;
struct dib8000_state {int seg_mask; scalar_t__ isdbt_cfg_loaded; int seg_diff_mask; TYPE_2__ cfg; } ;
struct TYPE_3__ {scalar_t__ ifreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ana_fe_coeff_13seg ; 
 int /*<<< orphan*/  dib8000_load_ana_fe_coefs (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8000_set_13seg_channel(struct dib8000_state *state)
{
	u16 i;
	u16 coff_pow = 0x2800;

	state->seg_mask = 0x1fff; /* All 13 segments enabled */

	/* ---- COFF ---- Carloff, the most robust --- */
	if (state->isdbt_cfg_loaded == 0) {  /* if not Sound Broadcasting mode : put default values for 13 segments */
		dib8000_write_word(state, 180, (16 << 6) | 9);
		dib8000_write_word(state, 187, (4 << 12) | (8 << 5) | 0x2);
		coff_pow = 0x2800;
		for (i = 0; i < 6; i++)
			dib8000_write_word(state, 181+i, coff_pow);

		/* P_ctrl_corm_thres4pre_freq_inh=1, P_ctrl_pre_freq_mode_sat=1 */
		/* P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 3, P_pre_freq_win_len=1 */
		dib8000_write_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (3 << 5) | 1);

		/* P_ctrl_pre_freq_win_len=8, P_ctrl_pre_freq_thres_lockin=6 */
		dib8000_write_word(state, 340, (8 << 6) | (6 << 0));
		/* P_ctrl_pre_freq_thres_lockout=4, P_small_use_tmcc/ac/cp=1 */
		dib8000_write_word(state, 341, (4 << 3) | (1 << 2) | (1 << 1) | (1 << 0));

		dib8000_write_word(state, 228, 0);  /* default value */
		dib8000_write_word(state, 265, 31); /* default value */
		dib8000_write_word(state, 205, 0x200f); /* init value */
	}

	/*
	 * make the cpil_coff_lock more robust but slower p_coff_winlen
	 * 6bits; p_coff_thres_lock 6bits (for coff lock if needed)
	 */

	if (state->cfg.pll->ifreq == 0)
		dib8000_write_word(state, 266, ~state->seg_mask | state->seg_diff_mask | 0x40); /* P_equal_noise_seg_inh */

	dib8000_load_ana_fe_coefs(state, ana_fe_coeff_13seg);
}