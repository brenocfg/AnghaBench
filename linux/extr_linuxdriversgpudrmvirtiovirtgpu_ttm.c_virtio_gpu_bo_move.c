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
struct ttm_operation_ctx {int /*<<< orphan*/  no_wait_gpu; int /*<<< orphan*/  interruptible; } ;
struct ttm_mem_reg {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int ttm_bo_wait (struct ttm_buffer_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_move_null (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 

__attribute__((used)) static int virtio_gpu_bo_move(struct ttm_buffer_object *bo, bool evict,
			      struct ttm_operation_ctx *ctx,
			      struct ttm_mem_reg *new_mem)
{
	int ret;

	ret = ttm_bo_wait(bo, ctx->interruptible, ctx->no_wait_gpu);
	if (ret)
		return ret;

	virtio_gpu_move_null(bo, new_mem);
	return 0;
}