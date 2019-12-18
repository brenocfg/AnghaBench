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
struct vmw_sw_context {int needs_post_query_barrier; int /*<<< orphan*/  ctx; struct vmw_buffer_object* cur_query_bo; int /*<<< orphan*/  last_query_ctx; struct vmw_res_cache_entry* res_cache; } ;
struct vmw_res_cache_entry {int /*<<< orphan*/  res; int /*<<< orphan*/  valid; } ;
struct vmw_private {int /*<<< orphan*/  has_mob; struct vmw_buffer_object* dummy_query_bo; } ;
struct TYPE_2__ {int num_pages; } ;
struct vmw_buffer_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 scalar_t__ unlikely (int) ; 
 size_t vmw_res_context ; 
 int vmw_validation_add_bo (int /*<<< orphan*/ ,struct vmw_buffer_object*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vmw_query_bo_switch_prepare(struct vmw_private *dev_priv,
				       struct vmw_buffer_object *new_query_bo,
				       struct vmw_sw_context *sw_context)
{
	struct vmw_res_cache_entry *ctx_entry =
		&sw_context->res_cache[vmw_res_context];
	int ret;

	BUG_ON(!ctx_entry->valid);
	sw_context->last_query_ctx = ctx_entry->res;

	if (unlikely(new_query_bo != sw_context->cur_query_bo)) {

		if (unlikely(new_query_bo->base.num_pages > 4)) {
			VMW_DEBUG_USER("Query buffer too large.\n");
			return -EINVAL;
		}

		if (unlikely(sw_context->cur_query_bo != NULL)) {
			sw_context->needs_post_query_barrier = true;
			ret = vmw_validation_add_bo(sw_context->ctx,
						    sw_context->cur_query_bo,
						    dev_priv->has_mob, false);
			if (unlikely(ret != 0))
				return ret;
		}
		sw_context->cur_query_bo = new_query_bo;

		ret = vmw_validation_add_bo(sw_context->ctx,
					    dev_priv->dummy_query_bo,
					    dev_priv->has_mob, false);
		if (unlikely(ret != 0))
			return ret;
	}

	return 0;
}