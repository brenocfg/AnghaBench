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
typedef  int u32 ;
struct xtpg_device {int npads; TYPE_1__* pattern; int /*<<< orphan*/  has_input; } ;
struct TYPE_2__ {int maximum; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_ctrl_modify_range (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void __xtpg_update_pattern_control(struct xtpg_device *xtpg,
					  bool passthrough, bool pattern)
{
	u32 pattern_mask = (1 << (xtpg->pattern->maximum + 1)) - 1;

	/*
	 * If the TPG has no sink pad or no input connected to its sink pad
	 * passthrough mode can't be enabled.
	 */
	if (xtpg->npads == 1 || !xtpg->has_input)
		passthrough = false;

	/* If passthrough mode is allowed unmask bit 0. */
	if (passthrough)
		pattern_mask &= ~1;

	/* If test pattern mode is allowed unmask all other bits. */
	if (pattern)
		pattern_mask &= 1;

	__v4l2_ctrl_modify_range(xtpg->pattern, 0, xtpg->pattern->maximum,
				 pattern_mask, pattern ? 9 : 0);
}