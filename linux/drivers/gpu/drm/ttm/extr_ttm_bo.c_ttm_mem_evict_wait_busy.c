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
struct ww_acquire_ctx {int dummy; } ;
struct ttm_operation_ctx {scalar_t__ interruptible; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {TYPE_1__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 int EDEADLK ; 
 int dma_resv_lock (int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int dma_resv_lock_interruptible (int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_mem_evict_wait_busy(struct ttm_buffer_object *busy_bo,
				   struct ttm_operation_ctx *ctx,
				   struct ww_acquire_ctx *ticket)
{
	int r;

	if (!busy_bo || !ticket)
		return -EBUSY;

	if (ctx->interruptible)
		r = dma_resv_lock_interruptible(busy_bo->base.resv,
							  ticket);
	else
		r = dma_resv_lock(busy_bo->base.resv, ticket);

	/*
	 * TODO: It would be better to keep the BO locked until allocation is at
	 * least tried one more time, but that would mean a much larger rework
	 * of TTM.
	 */
	if (!r)
		dma_resv_unlock(busy_bo->base.resv);

	return r == -EDEADLK ? -EBUSY : r;
}