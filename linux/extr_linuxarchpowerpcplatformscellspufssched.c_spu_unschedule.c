#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  invol_ctx_switch; } ;
struct spu_context {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  invol_ctx_switch; } ;
struct spu {int node; TYPE_1__ stats; int /*<<< orphan*/  alloc_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  list_mutex; int /*<<< orphan*/  nr_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_FREE ; 
 TYPE_3__* cbe_spu_info ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_unbind_context (struct spu*,struct spu_context*) ; 

__attribute__((used)) static void spu_unschedule(struct spu *spu, struct spu_context *ctx,
		int free_spu)
{
	int node = spu->node;

	mutex_lock(&cbe_spu_info[node].list_mutex);
	cbe_spu_info[node].nr_active--;
	if (free_spu)
		spu->alloc_state = SPU_FREE;
	spu_unbind_context(spu, ctx);
	ctx->stats.invol_ctx_switch++;
	spu->stats.invol_ctx_switch++;
	mutex_unlock(&cbe_spu_info[node].list_mutex);
}