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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
struct vmw_shader {void* num_output_sig; void* num_input_sig; int /*<<< orphan*/  type; void* size; } ;
struct vmw_resource {int /*<<< orphan*/  hw_destroy; int /*<<< orphan*/  backup_offset; int /*<<< orphan*/  backup; void* backup_size; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_resource*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_reference (struct vmw_buffer_object*) ; 
 int /*<<< orphan*/  vmw_gb_shader_func ; 
 int /*<<< orphan*/  vmw_hw_shader_destroy ; 
 struct vmw_shader* vmw_res_to_shader (struct vmw_resource*) ; 
 int vmw_resource_init (struct vmw_private*,struct vmw_resource*,int,void (*) (struct vmw_resource*),int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_gb_shader_init(struct vmw_private *dev_priv,
			      struct vmw_resource *res,
			      uint32_t size,
			      uint64_t offset,
			      SVGA3dShaderType type,
			      uint8_t num_input_sig,
			      uint8_t num_output_sig,
			      struct vmw_buffer_object *byte_code,
			      void (*res_free) (struct vmw_resource *res))
{
	struct vmw_shader *shader = vmw_res_to_shader(res);
	int ret;

	ret = vmw_resource_init(dev_priv, res, true, res_free,
				&vmw_gb_shader_func);

	if (unlikely(ret != 0)) {
		if (res_free)
			res_free(res);
		else
			kfree(res);
		return ret;
	}

	res->backup_size = size;
	if (byte_code) {
		res->backup = vmw_bo_reference(byte_code);
		res->backup_offset = offset;
	}
	shader->size = size;
	shader->type = type;
	shader->num_input_sig = num_input_sig;
	shader->num_output_sig = num_output_sig;

	res->hw_destroy = vmw_hw_shader_destroy;
	return 0;
}