#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  enum ps3av_mode_num { ____Placeholder_ps3av_mode_num } ps3av_mode_num ;
struct TYPE_3__ {int mask; int id; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int PS3AV_RES_MASK_50 ; 
 int PS3AV_RES_MASK_60 ; 
 int PS3AV_RES_MASK_VESA ; 
 int SHIFT_50 ; 
 int SHIFT_60 ; 
 int SHIFT_VESA ; 
 TYPE_1__* ps3av_preferred_modes ; 

__attribute__((used)) static enum ps3av_mode_num ps3av_resbit2id(u32 res_50, u32 res_60,
					   u32 res_vesa)
{
	unsigned int i;
	u32 res_all;

	/*
	 * We mask off the resolution bits we care about and combine the
	 * results in one bitfield, so make sure there's no overlap
	 */
	BUILD_BUG_ON(PS3AV_RES_MASK_50 << SHIFT_50 &
		     PS3AV_RES_MASK_60 << SHIFT_60);
	BUILD_BUG_ON(PS3AV_RES_MASK_50 << SHIFT_50 &
		     PS3AV_RES_MASK_VESA << SHIFT_VESA);
	BUILD_BUG_ON(PS3AV_RES_MASK_60 << SHIFT_60 &
		     PS3AV_RES_MASK_VESA << SHIFT_VESA);
	res_all = (res_50 & PS3AV_RES_MASK_50) << SHIFT_50 |
		  (res_60 & PS3AV_RES_MASK_60) << SHIFT_60 |
		  (res_vesa & PS3AV_RES_MASK_VESA) << SHIFT_VESA;

	if (!res_all)
		return 0;

	for (i = 0; i < ARRAY_SIZE(ps3av_preferred_modes); i++)
		if (res_all & ps3av_preferred_modes[i].mask)
			return ps3av_preferred_modes[i].id;

	return 0;
}