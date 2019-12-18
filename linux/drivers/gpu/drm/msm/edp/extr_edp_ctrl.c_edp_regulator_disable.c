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
struct edp_ctrl {int /*<<< orphan*/  vdda_vreg; int /*<<< orphan*/  lvl_vreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDDA_UA_OFF_LOAD ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_set_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_regulator_disable(struct edp_ctrl *ctrl)
{
	regulator_disable(ctrl->lvl_vreg);
	regulator_disable(ctrl->vdda_vreg);
	regulator_set_load(ctrl->vdda_vreg, VDDA_UA_OFF_LOAD);
}