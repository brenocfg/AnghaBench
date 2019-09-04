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
struct spu_context {int /*<<< orphan*/  run_wq; } ;
struct spu {int node; int /*<<< orphan*/  alloc_state; int /*<<< orphan*/ * ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_mutex; int /*<<< orphan*/  nr_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_USED ; 
 TYPE_1__* cbe_spu_info ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_add_to_rq (struct spu_context*) ; 
 int /*<<< orphan*/  spu_bind_context (struct spu*,struct spu_context*) ; 
 int /*<<< orphan*/  spu_set_timeslice (struct spu_context*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __spu_schedule(struct spu *spu, struct spu_context *ctx)
{
	int node = spu->node;
	int success = 0;

	spu_set_timeslice(ctx);

	mutex_lock(&cbe_spu_info[node].list_mutex);
	if (spu->ctx == NULL) {
		spu_bind_context(spu, ctx);
		cbe_spu_info[node].nr_active++;
		spu->alloc_state = SPU_USED;
		success = 1;
	}
	mutex_unlock(&cbe_spu_info[node].list_mutex);

	if (success)
		wake_up_all(&ctx->run_wq);
	else
		spu_add_to_rq(ctx);
}