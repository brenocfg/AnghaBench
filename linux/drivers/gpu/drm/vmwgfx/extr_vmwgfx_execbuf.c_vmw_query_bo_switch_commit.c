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
struct vmw_sw_context {scalar_t__ cur_query_bo; TYPE_1__* last_query_ctx; scalar_t__ needs_post_query_barrier; struct vmw_res_cache_entry* res_cache; } ;
struct vmw_resource {int /*<<< orphan*/  id; } ;
struct vmw_res_cache_entry {struct vmw_resource* res; int /*<<< orphan*/  valid; } ;
struct vmw_private {scalar_t__ pinned_bo; int dummy_query_bo_pinned; scalar_t__ dummy_query_bo; int query_cid_valid; int /*<<< orphan*/  query_cid; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (scalar_t__,int) ; 
 scalar_t__ vmw_bo_reference (scalar_t__) ; 
 int /*<<< orphan*/  vmw_bo_unreference (scalar_t__*) ; 
 int vmw_fifo_emit_dummy_query (struct vmw_private*,int /*<<< orphan*/ ) ; 
 size_t vmw_res_context ; 

__attribute__((used)) static void vmw_query_bo_switch_commit(struct vmw_private *dev_priv,
				     struct vmw_sw_context *sw_context)
{
	/*
	 * The validate list should still hold references to all
	 * contexts here.
	 */
	if (sw_context->needs_post_query_barrier) {
		struct vmw_res_cache_entry *ctx_entry =
			&sw_context->res_cache[vmw_res_context];
		struct vmw_resource *ctx;
		int ret;

		BUG_ON(!ctx_entry->valid);
		ctx = ctx_entry->res;

		ret = vmw_fifo_emit_dummy_query(dev_priv, ctx->id);

		if (unlikely(ret != 0))
			VMW_DEBUG_USER("Out of fifo space for dummy query.\n");
	}

	if (dev_priv->pinned_bo != sw_context->cur_query_bo) {
		if (dev_priv->pinned_bo) {
			vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
			vmw_bo_unreference(&dev_priv->pinned_bo);
		}

		if (!sw_context->needs_post_query_barrier) {
			vmw_bo_pin_reserved(sw_context->cur_query_bo, true);

			/*
			 * We pin also the dummy_query_bo buffer so that we
			 * don't need to validate it when emitting dummy queries
			 * in context destroy paths.
			 */
			if (!dev_priv->dummy_query_bo_pinned) {
				vmw_bo_pin_reserved(dev_priv->dummy_query_bo,
						    true);
				dev_priv->dummy_query_bo_pinned = true;
			}

			BUG_ON(sw_context->last_query_ctx == NULL);
			dev_priv->query_cid = sw_context->last_query_ctx->id;
			dev_priv->query_cid_valid = true;
			dev_priv->pinned_bo =
				vmw_bo_reference(sw_context->cur_query_bo);
		}
	}
}