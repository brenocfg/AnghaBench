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
struct dtv_frontend_properties {int /*<<< orphan*/  isdbt_partial_reception; int /*<<< orphan*/  isdbt_sb_mode; } ;
struct dib8000_state {int /*<<< orphan*/  mode; TYPE_1__** fe; } ;
typedef  enum param_loop_step { ____Placeholder_param_loop_step } param_loop_step ;
struct TYPE_2__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
#define  LOOP_TUNE_1 129 
#define  LOOP_TUNE_2 128 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8000_set_isdbt_loop_params(struct dib8000_state *state, enum param_loop_step loop_step)
{
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u16 reg_32 = 0, reg_37 = 0;

	switch (loop_step) {
	case LOOP_TUNE_1:
			if (c->isdbt_sb_mode)  {
				if (c->isdbt_partial_reception == 0) {
					reg_32 = ((11 - state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_alpha = (11-P_mode), P_corm_alpha=6, P_corm_thres=0x40 */
					reg_37 = (3 << 5) | (0 << 4) | (10 - state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = (10-P_mode)  */
				} else { /* Sound Broadcasting mode 3 seg */
					reg_32 = ((10 - state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_alpha = (10-P_mode), P_corm_alpha=6, P_corm_thres=0x60 */
					reg_37 = (3 << 5) | (0 << 4) | (9 - state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = (9-P_mode)  */
				}
			} else { /* 13-seg start conf offset loop parameters */
				reg_32 = ((9 - state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_alpha = (9-P_mode, P_corm_alpha=6, P_corm_thres=0x80 */
				reg_37 = (3 << 5) | (0 << 4) | (8 - state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = 9  */
			}
			break;
	case LOOP_TUNE_2:
			if (c->isdbt_sb_mode)  {
				if (c->isdbt_partial_reception == 0) {  /* Sound Broadcasting mode 1 seg */
					reg_32 = ((13-state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_alpha = (13-P_mode) , P_corm_alpha=6, P_corm_thres=0x40*/
					reg_37 = (12-state->mode) | ((5 + state->mode) << 5);
				} else {  /* Sound Broadcasting mode 3 seg */
					reg_32 = ((12-state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_alpha = (12-P_mode) , P_corm_alpha=6, P_corm_thres=0x60 */
					reg_37 = (11-state->mode) | ((5 + state->mode) << 5);
				}
			} else {  /* 13 seg */
				reg_32 = ((11-state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_alpha = 8 , P_corm_alpha=6, P_corm_thres=0x80 */
				reg_37 = ((5+state->mode) << 5) | (10 - state->mode);
			}
			break;
	}
	dib8000_write_word(state, 32, reg_32);
	dib8000_write_word(state, 37, reg_37);
}