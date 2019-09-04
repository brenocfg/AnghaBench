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
struct mpc {int dummy; } ;
struct dcn10_mpc {struct mpc base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn10_mpc_construct (struct dcn10_mpc*,struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct dcn10_mpc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_mask ; 
 int /*<<< orphan*/  mpc_regs ; 
 int /*<<< orphan*/  mpc_shift ; 

__attribute__((used)) static struct mpc *dcn10_mpc_create(struct dc_context *ctx)
{
	struct dcn10_mpc *mpc10 = kzalloc(sizeof(struct dcn10_mpc),
					  GFP_KERNEL);

	if (!mpc10)
		return NULL;

	dcn10_mpc_construct(mpc10, ctx,
			&mpc_regs,
			&mpc_shift,
			&mpc_mask,
			4);

	return &mpc10->base;
}