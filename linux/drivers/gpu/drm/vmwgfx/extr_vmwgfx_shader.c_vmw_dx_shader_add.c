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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_resource {int /*<<< orphan*/  hw_destroy; int /*<<< orphan*/  id; struct vmw_private* dev_priv; } ;
struct vmw_private {int dummy; } ;
struct vmw_dx_shader {int committed; int /*<<< orphan*/  id; int /*<<< orphan*/  cotable_head; int /*<<< orphan*/  cotable; struct vmw_resource* ctx; struct vmw_resource res; } ;
struct vmw_cmdbuf_res_manager {int dummy; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVGA_COTABLE_DXSHADER ; 
 struct vmw_dx_shader* kmalloc (int,int /*<<< orphan*/ ) ; 
 int ttm_mem_global_alloc (int /*<<< orphan*/ ,scalar_t__,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ttm_round_pot (int) ; 
 int vmw_cmdbuf_res_add (struct vmw_cmdbuf_res_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_resource*,struct list_head*) ; 
 int /*<<< orphan*/  vmw_cmdbuf_res_shader ; 
 int /*<<< orphan*/  vmw_context_cotable (struct vmw_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_dx_shader_func ; 
 int /*<<< orphan*/  vmw_dx_shader_res_free ; 
 int /*<<< orphan*/  vmw_hw_shader_destroy ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 int vmw_resource_init (struct vmw_private*,struct vmw_resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_resource_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 scalar_t__ vmw_shader_dx_size ; 
 int /*<<< orphan*/  vmw_shader_id_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_shader_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vmw_dx_shader_add(struct vmw_cmdbuf_res_manager *man,
		      struct vmw_resource *ctx,
		      u32 user_key,
		      SVGA3dShaderType shader_type,
		      struct list_head *list)
{
	struct vmw_dx_shader *shader;
	struct vmw_resource *res;
	struct vmw_private *dev_priv = ctx->dev_priv;
	struct ttm_operation_ctx ttm_opt_ctx = {
		.interruptible = true,
		.no_wait_gpu = false
	};
	int ret;

	if (!vmw_shader_dx_size)
		vmw_shader_dx_size = ttm_round_pot(sizeof(*shader));

	if (!vmw_shader_id_ok(user_key, shader_type))
		return -EINVAL;

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv), vmw_shader_dx_size,
				   &ttm_opt_ctx);
	if (ret) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for shader "
				  "creation.\n");
		return ret;
	}

	shader = kmalloc(sizeof(*shader), GFP_KERNEL);
	if (!shader) {
		ttm_mem_global_free(vmw_mem_glob(dev_priv), vmw_shader_dx_size);
		return -ENOMEM;
	}

	res = &shader->res;
	shader->ctx = ctx;
	shader->cotable = vmw_resource_reference
		(vmw_context_cotable(ctx, SVGA_COTABLE_DXSHADER));
	shader->id = user_key;
	shader->committed = false;
	INIT_LIST_HEAD(&shader->cotable_head);
	ret = vmw_resource_init(dev_priv, res, true,
				vmw_dx_shader_res_free, &vmw_dx_shader_func);
	if (ret)
		goto out_resource_init;

	/*
	 * The user_key name-space is not per shader type for DX shaders,
	 * so when hashing, use a single zero shader type.
	 */
	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_shader,
				 vmw_shader_key(user_key, 0),
				 res, list);
	if (ret)
		goto out_resource_init;

	res->id = shader->id;
	res->hw_destroy = vmw_hw_shader_destroy;

out_resource_init:
	vmw_resource_unreference(&res);

	return ret;
}