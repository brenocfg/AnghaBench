#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct TYPE_4__ {scalar_t__ mem_type; scalar_t__ start; } ;
struct ttm_buffer_object {scalar_t__ num_pages; scalar_t__ offset; TYPE_2__ mem; } ;
struct vmw_buffer_object {scalar_t__ pin_count; struct ttm_buffer_object base; } ;
struct ttm_placement {int num_placement; int num_busy_placement; struct ttm_place* busy_placement; struct ttm_place* placement; } ;
struct ttm_place {scalar_t__ lpfn; } ;
struct ttm_operation_ctx {int member_0; int member_1; int interruptible; } ;
struct TYPE_3__ {struct ttm_place* placement; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ttm_bo_mem_compat (struct ttm_placement*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_validate (struct ttm_buffer_object*,struct ttm_placement*,struct ttm_operation_ctx*) ; 
 int ttm_write_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_write_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (struct vmw_buffer_object*,int) ; 
 int /*<<< orphan*/  vmw_execbuf_release_pinned_bo (struct vmw_private*) ; 
 struct ttm_placement vmw_sys_placement ; 
 TYPE_1__ vmw_vram_placement ; 

int vmw_bo_pin_in_start_of_vram(struct vmw_private *dev_priv,
				struct vmw_buffer_object *buf,
				bool interruptible)
{
	struct ttm_operation_ctx ctx = {interruptible, false };
	struct ttm_buffer_object *bo = &buf->base;
	struct ttm_placement placement;
	struct ttm_place place;
	int ret = 0;
	uint32_t new_flags;

	place = vmw_vram_placement.placement[0];
	place.lpfn = bo->num_pages;
	placement.num_placement = 1;
	placement.placement = &place;
	placement.num_busy_placement = 1;
	placement.busy_placement = &place;

	ret = ttm_write_lock(&dev_priv->reservation_sem, interruptible);
	if (unlikely(ret != 0))
		return ret;

	vmw_execbuf_release_pinned_bo(dev_priv);
	ret = ttm_bo_reserve(bo, interruptible, false, NULL);
	if (unlikely(ret != 0))
		goto err_unlock;

	/*
	 * Is this buffer already in vram but not at the start of it?
	 * In that case, evict it first because TTM isn't good at handling
	 * that situation.
	 */
	if (bo->mem.mem_type == TTM_PL_VRAM &&
	    bo->mem.start < bo->num_pages &&
	    bo->mem.start > 0 &&
	    buf->pin_count == 0) {
		ctx.interruptible = false;
		(void) ttm_bo_validate(bo, &vmw_sys_placement, &ctx);
	}

	if (buf->pin_count > 0)
		ret = ttm_bo_mem_compat(&placement, &bo->mem,
					&new_flags) == true ? 0 : -EINVAL;
	else
		ret = ttm_bo_validate(bo, &placement, &ctx);

	/* For some reason we didn't end up at the start of vram */
	WARN_ON(ret == 0 && bo->offset != 0);
	if (!ret)
		vmw_bo_pin_reserved(buf, true);

	ttm_bo_unreserve(bo);
err_unlock:
	ttm_write_unlock(&dev_priv->reservation_sem);

	return ret;
}