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
typedef  int /*<<< orphan*/  u32 ;
struct edp_ctrl {int color_depth; scalar_t__ base; } ;
typedef  enum edp_color_depth { ____Placeholder_edp_color_depth } edp_color_depth ;

/* Variables and functions */
 int EDP_10BIT ; 
 int EDP_12BIT ; 
 int EDP_16BIT ; 
 int EDP_6BIT ; 
 int EDP_8BIT ; 
 int /*<<< orphan*/  EDP_MISC1_MISC0_COLOR (int) ; 
 int /*<<< orphan*/  EDP_MISC1_MISC0_SYNC ; 
 scalar_t__ REG_EDP_MISC1_MISC0 ; 
 int /*<<< orphan*/  edp_read (scalar_t__) ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_clock_synchrous(struct edp_ctrl *ctrl, int sync)
{
	u32 data;
	enum edp_color_depth depth;

	data = edp_read(ctrl->base + REG_EDP_MISC1_MISC0);

	if (sync)
		data |= EDP_MISC1_MISC0_SYNC;
	else
		data &= ~EDP_MISC1_MISC0_SYNC;

	/* only legacy rgb mode supported */
	depth = EDP_6BIT; /* Default */
	if (ctrl->color_depth == 8)
		depth = EDP_8BIT;
	else if (ctrl->color_depth == 10)
		depth = EDP_10BIT;
	else if (ctrl->color_depth == 12)
		depth = EDP_12BIT;
	else if (ctrl->color_depth == 16)
		depth = EDP_16BIT;

	data |= EDP_MISC1_MISC0_COLOR(depth);

	edp_write(ctrl->base + REG_EDP_MISC1_MISC0, data);
}