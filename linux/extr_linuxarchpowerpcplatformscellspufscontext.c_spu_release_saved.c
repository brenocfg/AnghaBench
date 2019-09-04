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
struct spu_context {scalar_t__ state; int /*<<< orphan*/  sched_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SPU_SCHED_SPU_RUN ; 
 int /*<<< orphan*/  SPU_SCHED_WAS_ACTIVE ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int /*<<< orphan*/  spu_activate (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void spu_release_saved(struct spu_context *ctx)
{
	BUG_ON(ctx->state != SPU_STATE_SAVED);

	if (test_and_clear_bit(SPU_SCHED_WAS_ACTIVE, &ctx->sched_flags) &&
			test_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags))
		spu_activate(ctx, 0);

	spu_release(ctx);
}