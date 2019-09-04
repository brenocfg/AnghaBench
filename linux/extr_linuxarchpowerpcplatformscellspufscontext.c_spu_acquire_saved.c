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
 int /*<<< orphan*/  SPU_SCHED_WAS_ACTIVE ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_acquire_saved__enter ; 
 int /*<<< orphan*/  spu_context_nospu_trace (int /*<<< orphan*/ ,struct spu_context*) ; 
 int /*<<< orphan*/  spu_deactivate (struct spu_context*) ; 

int spu_acquire_saved(struct spu_context *ctx)
{
	int ret;

	spu_context_nospu_trace(spu_acquire_saved__enter, ctx);

	ret = spu_acquire(ctx);
	if (ret)
		return ret;

	if (ctx->state != SPU_STATE_SAVED) {
		set_bit(SPU_SCHED_WAS_ACTIVE, &ctx->sched_flags);
		spu_deactivate(ctx);
	}

	return 0;
}