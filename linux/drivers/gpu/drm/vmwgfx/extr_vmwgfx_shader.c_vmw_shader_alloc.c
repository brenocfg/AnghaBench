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
struct vmw_resource {int dummy; } ;
struct vmw_shader {struct vmw_resource res; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 struct vmw_resource* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VMW_IDA_ACC_SIZE ; 
 struct vmw_shader* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ttm_mem_global_alloc (int /*<<< orphan*/ ,scalar_t__,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ttm_round_pot (int) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_gb_shader_init (struct vmw_private*,struct vmw_resource*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_shader_free ; 
 scalar_t__ vmw_shader_size ; 

__attribute__((used)) static struct vmw_resource *vmw_shader_alloc(struct vmw_private *dev_priv,
					     struct vmw_buffer_object *buffer,
					     size_t shader_size,
					     size_t offset,
					     SVGA3dShaderType shader_type)
{
	struct vmw_shader *shader;
	struct vmw_resource *res;
	struct ttm_operation_ctx ctx = {
		.interruptible = true,
		.no_wait_gpu = false
	};
	int ret;

	if (unlikely(vmw_shader_size == 0))
		vmw_shader_size =
			ttm_round_pot(sizeof(struct vmw_shader)) +
			VMW_IDA_ACC_SIZE;

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_shader_size,
				   &ctx);
	if (unlikely(ret != 0)) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for shader "
				  "creation.\n");
		goto out_err;
	}

	shader = kzalloc(sizeof(*shader), GFP_KERNEL);
	if (unlikely(!shader)) {
		ttm_mem_global_free(vmw_mem_glob(dev_priv),
				    vmw_shader_size);
		ret = -ENOMEM;
		goto out_err;
	}

	res = &shader->res;

	/*
	 * From here on, the destructor takes over resource freeing.
	 */
	ret = vmw_gb_shader_init(dev_priv, res, shader_size,
				 offset, shader_type, 0, 0, buffer,
				 vmw_shader_free);

out_err:
	return ret ? ERR_PTR(ret) : res;
}