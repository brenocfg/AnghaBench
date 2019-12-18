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
struct vmw_resource {struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  binding_mutex; } ;
struct vmw_fence_obj {int dummy; } ;
struct vmw_cotable {int /*<<< orphan*/  ctx; int /*<<< orphan*/  scrubbed; } ;
struct ttm_validate_buffer {struct ttm_buffer_object* bo; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_3__ {scalar_t__ mem_type; } ;
struct ttm_buffer_object {TYPE_2__ base; TYPE_1__ mem; } ;

/* Variables and functions */
 scalar_t__ VMW_PL_MOB ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_fence_single (struct ttm_buffer_object*,struct vmw_fence_obj*) ; 
 struct vmw_cotable* vmw_cotable (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_dx_context_scrub_cotables (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_execbuf_fence_commands (int /*<<< orphan*/ *,struct vmw_private*,struct vmw_fence_obj**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fence_obj_unreference (struct vmw_fence_obj**) ; 
 int /*<<< orphan*/  vmw_resource_mob_attached (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_cotable_unbind(struct vmw_resource *res,
			      bool readback,
			      struct ttm_validate_buffer *val_buf)
{
	struct vmw_cotable *vcotbl = vmw_cotable(res);
	struct vmw_private *dev_priv = res->dev_priv;
	struct ttm_buffer_object *bo = val_buf->bo;
	struct vmw_fence_obj *fence;

	if (!vmw_resource_mob_attached(res))
		return 0;

	WARN_ON_ONCE(bo->mem.mem_type != VMW_PL_MOB);
	dma_resv_assert_held(bo->base.resv);

	mutex_lock(&dev_priv->binding_mutex);
	if (!vcotbl->scrubbed)
		vmw_dx_context_scrub_cotables(vcotbl->ctx, readback);
	mutex_unlock(&dev_priv->binding_mutex);
	(void) vmw_execbuf_fence_commands(NULL, dev_priv, &fence, NULL);
	vmw_bo_fence_single(bo, fence);
	if (likely(fence != NULL))
		vmw_fence_obj_unreference(&fence);

	return 0;
}