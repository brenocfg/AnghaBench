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
 scalar_t__ REG_EDP_STATE_CTRL ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void edp_state_ctrl(struct edp_ctrl *ctrl, u32 state)
{
	edp_write(ctrl->base + REG_EDP_STATE_CTRL, state);
	/* Make sure H/W status is set */
	wmb();
}