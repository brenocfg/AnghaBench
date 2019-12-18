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
typedef  int u32 ;
struct TYPE_4__ {unsigned long key; } ;
struct vmw_validation_res_node {int first_usage; int dirty_set; int dirty; int /*<<< orphan*/  private; int /*<<< orphan*/  head; int /*<<< orphan*/  res; TYPE_2__ hash; } ;
struct vmw_validation_context {int /*<<< orphan*/  resource_list; int /*<<< orphan*/  resource_ctx_list; scalar_t__ ht; } ;
struct vmw_resource {TYPE_1__* dev_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_mob; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 int VMW_RES_DIRTY_SET ; 
 int drm_ht_insert_item (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  vmw_res_context 130 
#define  vmw_res_cotable 129 
#define  vmw_res_dx_context 128 
 int vmw_res_type (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_reference_unless_doomed (struct vmw_resource*) ; 
 struct vmw_validation_res_node* vmw_validation_find_res_dup (struct vmw_validation_context*,struct vmw_resource*) ; 
 struct vmw_validation_res_node* vmw_validation_mem_alloc (struct vmw_validation_context*,int) ; 

int vmw_validation_add_resource(struct vmw_validation_context *ctx,
				struct vmw_resource *res,
				size_t priv_size,
				u32 dirty,
				void **p_node,
				bool *first_usage)
{
	struct vmw_validation_res_node *node;
	int ret;

	node = vmw_validation_find_res_dup(ctx, res);
	if (node) {
		node->first_usage = 0;
		goto out_fill;
	}

	node = vmw_validation_mem_alloc(ctx, sizeof(*node) + priv_size);
	if (!node) {
		VMW_DEBUG_USER("Failed to allocate a resource validation entry.\n");
		return -ENOMEM;
	}

	if (ctx->ht) {
		node->hash.key = (unsigned long) res;
		ret = drm_ht_insert_item(ctx->ht, &node->hash);
		if (ret) {
			DRM_ERROR("Failed to initialize a resource validation "
				  "entry.\n");
			return ret;
		}
	}
	node->res = vmw_resource_reference_unless_doomed(res);
	if (!node->res)
		return -ESRCH;

	node->first_usage = 1;
	if (!res->dev_priv->has_mob) {
		list_add_tail(&node->head, &ctx->resource_list);
	} else {
		switch (vmw_res_type(res)) {
		case vmw_res_context:
		case vmw_res_dx_context:
			list_add(&node->head, &ctx->resource_ctx_list);
			break;
		case vmw_res_cotable:
			list_add_tail(&node->head, &ctx->resource_ctx_list);
			break;
		default:
			list_add_tail(&node->head, &ctx->resource_list);
			break;
		}
	}

out_fill:
	if (dirty) {
		node->dirty_set = 1;
		/* Overwriting previous information here is intentional! */
		node->dirty = (dirty & VMW_RES_DIRTY_SET) ? 1 : 0;
	}
	if (first_usage)
		*first_usage = node->first_usage;
	if (p_node)
		*p_node = &node->private;

	return 0;
}