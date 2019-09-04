#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct vmw_private {int query_cid_valid; int dummy_query_bo_pinned; TYPE_1__* pinned_bo; TYPE_1__* dummy_query_bo; int /*<<< orphan*/  query_cid; } ;
struct vmw_fence_obj {int dummy; } ;
struct ttm_validate_buffer {int shared; void* bo; int /*<<< orphan*/  head; } ;
struct list_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 void* ttm_bo_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unref (void**) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int /*<<< orphan*/  ttm_eu_fence_buffer_objects (struct ww_acquire_ctx*,struct list_head*,void*) ; 
 int ttm_eu_reserve_buffers (struct ww_acquire_ctx*,struct list_head*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (TYPE_1__**) ; 
 int /*<<< orphan*/  vmw_execbuf_fence_commands (int /*<<< orphan*/ *,struct vmw_private*,struct vmw_fence_obj**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_execbuf_unpin_panic (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fence_obj_unreference (struct vmw_fence_obj**) ; 
 int vmw_fifo_emit_dummy_query (struct vmw_private*,int /*<<< orphan*/ ) ; 

void __vmw_execbuf_release_pinned_bo(struct vmw_private *dev_priv,
				     struct vmw_fence_obj *fence)
{
	int ret = 0;
	struct list_head validate_list;
	struct ttm_validate_buffer pinned_val, query_val;
	struct vmw_fence_obj *lfence = NULL;
	struct ww_acquire_ctx ticket;

	if (dev_priv->pinned_bo == NULL)
		goto out_unlock;

	INIT_LIST_HEAD(&validate_list);

	pinned_val.bo = ttm_bo_reference(&dev_priv->pinned_bo->base);
	pinned_val.shared = false;
	list_add_tail(&pinned_val.head, &validate_list);

	query_val.bo = ttm_bo_reference(&dev_priv->dummy_query_bo->base);
	query_val.shared = false;
	list_add_tail(&query_val.head, &validate_list);

	ret = ttm_eu_reserve_buffers(&ticket, &validate_list,
				     false, NULL);
	if (unlikely(ret != 0)) {
		vmw_execbuf_unpin_panic(dev_priv);
		goto out_no_reserve;
	}

	if (dev_priv->query_cid_valid) {
		BUG_ON(fence != NULL);
		ret = vmw_fifo_emit_dummy_query(dev_priv, dev_priv->query_cid);
		if (unlikely(ret != 0)) {
			vmw_execbuf_unpin_panic(dev_priv);
			goto out_no_emit;
		}
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
	ttm_eu_fence_buffer_objects(&ticket, &validate_list, (void *) fence);
	if (lfence != NULL)
		vmw_fence_obj_unreference(&lfence);

	ttm_bo_unref(&query_val.bo);
	ttm_bo_unref(&pinned_val.bo);
	vmw_bo_unreference(&dev_priv->pinned_bo);
out_unlock:
	return;

out_no_emit:
	ttm_eu_backoff_reservation(&ticket, &validate_list);
out_no_reserve:
	ttm_bo_unref(&query_val.bo);
	ttm_bo_unref(&pinned_val.bo);
	vmw_bo_unreference(&dev_priv->pinned_bo);
}