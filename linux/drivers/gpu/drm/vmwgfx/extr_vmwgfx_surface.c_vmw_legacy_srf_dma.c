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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_surface {int dummy; } ;
struct vmw_resource {struct vmw_private* dev_priv; } ;
struct vmw_private {int dummy; } ;
struct vmw_fence_obj {int dummy; } ;
struct ttm_validate_buffer {int /*<<< orphan*/  bo; } ;
typedef  int /*<<< orphan*/  SVGAGuestPtr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * VMW_FIFO_RESERVE (struct vmw_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_fence_single (int /*<<< orphan*/ ,struct vmw_fence_obj*) ; 
 int /*<<< orphan*/  vmw_bo_get_guest_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_execbuf_fence_commands (int /*<<< orphan*/ *,struct vmw_private*,struct vmw_fence_obj**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fence_obj_unreference (struct vmw_fence_obj**) ; 
 int /*<<< orphan*/  vmw_fifo_commit (struct vmw_private*,int /*<<< orphan*/ ) ; 
 struct vmw_surface* vmw_res_to_srf (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_surface_dma_encode (struct vmw_surface*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_surface_dma_size (struct vmw_surface*) ; 

__attribute__((used)) static int vmw_legacy_srf_dma(struct vmw_resource *res,
			      struct ttm_validate_buffer *val_buf,
			      bool bind)
{
	SVGAGuestPtr ptr;
	struct vmw_fence_obj *fence;
	uint32_t submit_size;
	struct vmw_surface *srf = vmw_res_to_srf(res);
	uint8_t *cmd;
	struct vmw_private *dev_priv = res->dev_priv;

	BUG_ON(!val_buf->bo);
	submit_size = vmw_surface_dma_size(srf);
	cmd = VMW_FIFO_RESERVE(dev_priv, submit_size);
	if (unlikely(!cmd))
		return -ENOMEM;

	vmw_bo_get_guest_ptr(val_buf->bo, &ptr);
	vmw_surface_dma_encode(srf, cmd, &ptr, bind);

	vmw_fifo_commit(dev_priv, submit_size);

	/*
	 * Create a fence object and fence the backup buffer.
	 */

	(void) vmw_execbuf_fence_commands(NULL, dev_priv,
					  &fence, NULL);

	vmw_bo_fence_single(val_buf->bo, fence);

	if (likely(fence != NULL))
		vmw_fence_obj_unreference(&fence);

	return 0;
}