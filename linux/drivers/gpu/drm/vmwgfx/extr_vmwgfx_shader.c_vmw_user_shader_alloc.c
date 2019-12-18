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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int shareable; int /*<<< orphan*/  handle; int /*<<< orphan*/ * tfile; } ;
struct vmw_resource {int dummy; } ;
struct TYPE_3__ {struct vmw_resource res; } ;
struct vmw_user_shader {TYPE_2__ base; TYPE_1__ shader; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct ttm_object_file {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TTM_OBJ_EXTRA_SIZE ; 
 scalar_t__ VMW_IDA_ACC_SIZE ; 
 int /*<<< orphan*/  VMW_RES_SHADER ; 
 struct vmw_user_shader* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ttm_base_object_init (struct ttm_object_file*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ttm_mem_global_alloc (int /*<<< orphan*/ ,scalar_t__,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ttm_round_pot (int) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_gb_shader_init (struct vmw_private*,struct vmw_resource*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 struct vmw_resource* vmw_resource_reference (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 int /*<<< orphan*/  vmw_user_shader_base_release ; 
 int /*<<< orphan*/  vmw_user_shader_free ; 
 scalar_t__ vmw_user_shader_size ; 

__attribute__((used)) static int vmw_user_shader_alloc(struct vmw_private *dev_priv,
				 struct vmw_buffer_object *buffer,
				 size_t shader_size,
				 size_t offset,
				 SVGA3dShaderType shader_type,
				 uint8_t num_input_sig,
				 uint8_t num_output_sig,
				 struct ttm_object_file *tfile,
				 u32 *handle)
{
	struct vmw_user_shader *ushader;
	struct vmw_resource *res, *tmp;
	struct ttm_operation_ctx ctx = {
		.interruptible = true,
		.no_wait_gpu = false
	};
	int ret;

	if (unlikely(vmw_user_shader_size == 0))
		vmw_user_shader_size =
			ttm_round_pot(sizeof(struct vmw_user_shader)) +
			VMW_IDA_ACC_SIZE + TTM_OBJ_EXTRA_SIZE;

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_user_shader_size,
				   &ctx);
	if (unlikely(ret != 0)) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for shader "
				  "creation.\n");
		goto out;
	}

	ushader = kzalloc(sizeof(*ushader), GFP_KERNEL);
	if (unlikely(!ushader)) {
		ttm_mem_global_free(vmw_mem_glob(dev_priv),
				    vmw_user_shader_size);
		ret = -ENOMEM;
		goto out;
	}

	res = &ushader->shader.res;
	ushader->base.shareable = false;
	ushader->base.tfile = NULL;

	/*
	 * From here on, the destructor takes over resource freeing.
	 */

	ret = vmw_gb_shader_init(dev_priv, res, shader_size,
				 offset, shader_type, num_input_sig,
				 num_output_sig, buffer,
				 vmw_user_shader_free);
	if (unlikely(ret != 0))
		goto out;

	tmp = vmw_resource_reference(res);
	ret = ttm_base_object_init(tfile, &ushader->base, false,
				   VMW_RES_SHADER,
				   &vmw_user_shader_base_release, NULL);

	if (unlikely(ret != 0)) {
		vmw_resource_unreference(&tmp);
		goto out_err;
	}

	if (handle)
		*handle = ushader->base.handle;
out_err:
	vmw_resource_unreference(&res);
out:
	return ret;
}