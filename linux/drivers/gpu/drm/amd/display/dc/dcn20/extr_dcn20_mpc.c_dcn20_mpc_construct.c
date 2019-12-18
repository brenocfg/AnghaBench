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
struct dcn20_mpc_shift {int dummy; } ;
struct dcn20_mpc_registers {int dummy; } ;
struct dcn20_mpc_mask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mpcc_array; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dcn20_mpc {int num_mpcc; TYPE_1__ base; scalar_t__ mpcc_in_use_mask; struct dcn20_mpc_mask const* mpc_mask; struct dcn20_mpc_shift const* mpc_shift; struct dcn20_mpc_registers const* mpc_regs; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int MAX_MPCC ; 
 int /*<<< orphan*/  dcn20_mpc_funcs ; 
 int /*<<< orphan*/  mpc2_init_mpcc (int /*<<< orphan*/ *,int) ; 

void dcn20_mpc_construct(struct dcn20_mpc *mpc20,
	struct dc_context *ctx,
	const struct dcn20_mpc_registers *mpc_regs,
	const struct dcn20_mpc_shift *mpc_shift,
	const struct dcn20_mpc_mask *mpc_mask,
	int num_mpcc)
{
	int i;

	mpc20->base.ctx = ctx;

	mpc20->base.funcs = &dcn20_mpc_funcs;

	mpc20->mpc_regs = mpc_regs;
	mpc20->mpc_shift = mpc_shift;
	mpc20->mpc_mask = mpc_mask;

	mpc20->mpcc_in_use_mask = 0;
	mpc20->num_mpcc = num_mpcc;

	for (i = 0; i < MAX_MPCC; i++)
		mpc2_init_mpcc(&mpc20->base.mpcc_array[i], i);
}