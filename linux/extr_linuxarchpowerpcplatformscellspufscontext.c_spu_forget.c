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
struct spu_context {scalar_t__ state; struct mm_struct* owner; int /*<<< orphan*/  state_mutex; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPU_STATE_SAVED ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_deactivate (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 

void spu_forget(struct spu_context *ctx)
{
	struct mm_struct *mm;

	/*
	 * This is basically an open-coded spu_acquire_saved, except that
	 * we don't acquire the state mutex interruptible, and we don't
	 * want this context to be rescheduled on release.
	 */
	mutex_lock(&ctx->state_mutex);
	if (ctx->state != SPU_STATE_SAVED)
		spu_deactivate(ctx);

	mm = ctx->owner;
	ctx->owner = NULL;
	mmput(mm);
	spu_release(ctx);
}