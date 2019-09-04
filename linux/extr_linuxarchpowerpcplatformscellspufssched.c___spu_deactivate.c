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
struct spu_context {int flags; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  stop_wq; struct spu* spu; } ;
struct spu {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int SPU_CREATE_NOSCHED ; 
 struct spu_context* grab_runnable_context (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  spu_schedule (struct spu*,struct spu_context*) ; 
 int /*<<< orphan*/  spu_unschedule (struct spu*,struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __spu_deactivate(struct spu_context *ctx, int force, int max_prio)
{
	struct spu *spu = ctx->spu;
	struct spu_context *new = NULL;

	if (spu) {
		new = grab_runnable_context(max_prio, spu->node);
		if (new || force) {
			spu_unschedule(spu, ctx, new == NULL);
			if (new) {
				if (new->flags & SPU_CREATE_NOSCHED)
					wake_up(&new->stop_wq);
				else {
					spu_release(ctx);
					spu_schedule(spu, new);
					/* this one can't easily be made
					   interruptible */
					mutex_lock(&ctx->state_mutex);
				}
			}
		}
	}

	return new != NULL;
}