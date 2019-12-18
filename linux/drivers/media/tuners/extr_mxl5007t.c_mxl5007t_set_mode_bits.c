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
struct mxl5007t_state {int /*<<< orphan*/  tab_init_cable; int /*<<< orphan*/  tab_init; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum mxl5007t_mode { ____Placeholder_mxl5007t_mode } mxl5007t_mode ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  MxL_MODE_ATSC 131 
#define  MxL_MODE_CABLE 130 
#define  MxL_MODE_DVBT 129 
#define  MxL_MODE_ISDBT 128 
 int /*<<< orphan*/  mxl_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void mxl5007t_set_mode_bits(struct mxl5007t_state *state,
				   enum mxl5007t_mode mode,
				   s32 if_diff_out_level)
{
	switch (mode) {
	case MxL_MODE_ATSC:
		set_reg_bits(state->tab_init, 0x06, 0x1f, 0x12);
		break;
	case MxL_MODE_DVBT:
		set_reg_bits(state->tab_init, 0x06, 0x1f, 0x11);
		break;
	case MxL_MODE_ISDBT:
		set_reg_bits(state->tab_init, 0x06, 0x1f, 0x10);
		break;
	case MxL_MODE_CABLE:
		set_reg_bits(state->tab_init_cable, 0x09, 0xff, 0xc1);
		set_reg_bits(state->tab_init_cable, 0x0a, 0xff,
			     8 - if_diff_out_level);
		set_reg_bits(state->tab_init_cable, 0x0b, 0xff, 0x17);
		break;
	default:
		mxl_fail(-EINVAL);
	}
	return;
}