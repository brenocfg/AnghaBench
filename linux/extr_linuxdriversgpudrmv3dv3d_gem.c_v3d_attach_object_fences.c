#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* s_fence; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct v3d_exec_info {int bo_count; TYPE_4__** bo; TYPE_3__ render; } ;
struct v3d_bo {int /*<<< orphan*/  resv; } ;
struct dma_fence {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {struct dma_fence finished; } ;

/* Variables and functions */
 int /*<<< orphan*/  reservation_object_add_excl_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 struct v3d_bo* to_v3d_bo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
v3d_attach_object_fences(struct v3d_exec_info *exec)
{
	struct dma_fence *out_fence = &exec->render.base.s_fence->finished;
	struct v3d_bo *bo;
	int i;

	for (i = 0; i < exec->bo_count; i++) {
		bo = to_v3d_bo(&exec->bo[i]->base);

		/* XXX: Use shared fences for read-only objects. */
		reservation_object_add_excl_fence(bo->resv, out_fence);
	}
}