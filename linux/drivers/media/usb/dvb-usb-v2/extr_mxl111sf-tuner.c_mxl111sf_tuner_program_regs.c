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
struct mxl111sf_tuner_state {int /*<<< orphan*/  mxl_state; TYPE_1__* cfg; } ;
struct mxl111sf_reg_ctrl_info {int dummy; } ;
struct TYPE_2__ {int (* program_regs ) (int /*<<< orphan*/ ,struct mxl111sf_reg_ctrl_info*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,struct mxl111sf_reg_ctrl_info*) ; 

__attribute__((used)) static int mxl111sf_tuner_program_regs(struct mxl111sf_tuner_state *state,
			       struct mxl111sf_reg_ctrl_info *ctrl_reg_info)
{
	return (state->cfg->program_regs) ?
		state->cfg->program_regs(state->mxl_state, ctrl_reg_info) :
		-EINVAL;
}