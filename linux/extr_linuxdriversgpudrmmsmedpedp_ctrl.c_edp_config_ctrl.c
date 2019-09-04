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
struct TYPE_2__ {int capabilities; } ;
struct edp_ctrl {int color_depth; scalar_t__ base; int /*<<< orphan*/  interlaced; TYPE_1__ dp_link; scalar_t__ lane_cnt; } ;
typedef  enum edp_color_depth { ____Placeholder_edp_color_depth } edp_color_depth ;

/* Variables and functions */
 int DP_LINK_CAP_ENHANCED_FRAMING ; 
 int EDP_6BIT ; 
 int EDP_8BIT ; 
 int EDP_CONFIGURATION_CTRL_COLOR (int) ; 
 int EDP_CONFIGURATION_CTRL_ENHANCED_FRAMING ; 
 int EDP_CONFIGURATION_CTRL_LANES (scalar_t__) ; 
 int EDP_CONFIGURATION_CTRL_PROGRESSIVE ; 
 int EDP_CONFIGURATION_CTRL_STATIC_MVID ; 
 int EDP_CONFIGURATION_CTRL_SYNC_CLK ; 
 scalar_t__ REG_EDP_CONFIGURATION_CTRL ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int) ; 

__attribute__((used)) static void edp_config_ctrl(struct edp_ctrl *ctrl)
{
	u32 data;
	enum edp_color_depth depth;

	data = EDP_CONFIGURATION_CTRL_LANES(ctrl->lane_cnt - 1);

	if (ctrl->dp_link.capabilities & DP_LINK_CAP_ENHANCED_FRAMING)
		data |= EDP_CONFIGURATION_CTRL_ENHANCED_FRAMING;

	depth = EDP_6BIT;
	if (ctrl->color_depth == 8)
		depth = EDP_8BIT;

	data |= EDP_CONFIGURATION_CTRL_COLOR(depth);

	if (!ctrl->interlaced)	/* progressive */
		data |= EDP_CONFIGURATION_CTRL_PROGRESSIVE;

	data |= (EDP_CONFIGURATION_CTRL_SYNC_CLK |
		EDP_CONFIGURATION_CTRL_STATIC_MVID);

	edp_write(ctrl->base + REG_EDP_CONFIGURATION_CTRL, data);
}