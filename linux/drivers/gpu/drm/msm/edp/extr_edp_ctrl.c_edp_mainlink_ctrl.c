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
struct edp_ctrl {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_MAINLINK_CTRL_ENABLE ; 
 int /*<<< orphan*/  EDP_MAINLINK_CTRL_RESET ; 
 scalar_t__ REG_EDP_MAINLINK_CTRL ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void edp_mainlink_ctrl(struct edp_ctrl *ctrl, int enable)
{
	u32 data = 0;

	edp_write(ctrl->base + REG_EDP_MAINLINK_CTRL, EDP_MAINLINK_CTRL_RESET);
	/* Make sure fully reset */
	wmb();
	usleep_range(500, 1000);

	if (enable)
		data |= EDP_MAINLINK_CTRL_ENABLE;

	edp_write(ctrl->base + REG_EDP_MAINLINK_CTRL, data);
}