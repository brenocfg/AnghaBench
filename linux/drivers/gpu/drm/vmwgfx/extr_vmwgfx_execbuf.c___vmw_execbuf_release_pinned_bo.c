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
struct vmw_private {int query_cid_valid; int dummy_query_bo_pinned; int /*<<< orphan*/ * pinned_bo; int /*<<< orphan*/ * dummy_query_bo; int /*<<< orphan*/  query_cid; } ;
struct vmw_fence_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_VAL_CONTEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_ctx ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vmw_execbuf_fence_commands (int /*<<< orphan*/ *,struct vmw_private*,struct vmw_fence_obj**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_execbuf_unpin_panic (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fence_obj_unreference (struct vmw_fence_obj**) ; 
 int vmw_fifo_emit_dummy_query (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int vmw_validation_add_bo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vmw_validation_bo_backoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_validation_bo_fence (int /*<<< orphan*/ *,struct vmw_fence_obj*) ; 
 int vmw_validation_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_validation_unref_lists (int /*<<< orphan*/ *) ; 

void __vmw_execbuf_release_pinned_bo(struct vmw_private *dev_priv,
				     struct vmw_fence_obj *fence)
{
	int ret = 0;
	struct vmw_fence_obj *lfence = NULL;
	DECLARE_VAL_CONTEXT(val_ctx, NULL, 0);

	if (dev_priv->pinned_bo == NULL)
		goto out_unlock;

	ret = vmw_validation_add_bo(&val_ctx, dev_priv->pinned_bo, false,
				    false);
	if (ret)
		goto out_no_reserve;

	ret = vmw_validation_add_bo(&val_ctx, dev_priv->dummy_query_bo, false,
				    false);
	if (ret)
		goto out_no_reserve;

	ret = vmw_validation_bo_reserve(&val_ctx, false);
	if (ret)
		goto out_no_reserve;

	if (dev_priv->query_cid_valid) {
		BUG_ON(fence != NULL);
		ret = vmw_fifo_emit_dummy_query(dev_priv, dev_priv->query_cid);
		if (ret)
			goto out_no_emit;
		dev_priv->query_cid_valid = false;
	}

	vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
	if (dev_priv->dummy_query_bo_pinned) {
		vmw_bo_pin_reserved(dev_priv->dummy_query_bo, false);
		dev_priv->dummy_query_bo_pinned = false;
	}
	if (fence == NULL) {
		(void) vmw_execbuf_fence_commands(NULL, dev_priv, &lfence,
						  NULL);
		fence = lfence;
	}
	vmw_validation_bo_fence(&val_ctx, fence);
	if (lfence != NULL)
		vmw_fence_obj_unreference(&lfence);

	vmw_validation_unref_lists(&val_ctx);
	vmw_bo_unreference(&dev_priv->pinned_bo);

out_unlock:
	return;
out_no_emit:
	vmw_validation_bo_backoff(&val_ctx);
out_no_reserve:
	vmw_validation_unref_lists(&val_ctx);
	vmw_execbuf_unpin_panic(dev_priv);
	vmw_bo_unreference(&dev_priv->pinned_bo);
}