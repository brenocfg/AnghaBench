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
struct TYPE_2__ {int (* top_master_ctrl ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxl1x1sf_tuner_top_master_ctrl(struct mxl111sf_tuner_state *state,
					  int onoff)
{
	return (state->cfg->top_master_ctrl) ?
		state->cfg->top_master_ctrl(state->mxl_state, onoff) :
		-EINVAL;
}