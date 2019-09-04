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
typedef  int /*<<< orphan*/  u8 ;
struct mxl111sf_tuner_state {int /*<<< orphan*/  mxl_state; TYPE_1__* cfg; } ;
struct TYPE_2__ {int (* write_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxl111sf_tuner_write_reg(struct mxl111sf_tuner_state *state,
				    u8 addr, u8 data)
{
	return (state->cfg->write_reg) ?
		state->cfg->write_reg(state->mxl_state, addr, data) :
		-EINVAL;
}