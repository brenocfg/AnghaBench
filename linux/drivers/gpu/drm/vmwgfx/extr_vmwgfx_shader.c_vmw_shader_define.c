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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct TYPE_3__ {scalar_t__ num_pages; } ;
struct vmw_buffer_object {TYPE_1__ base; } ;
struct ttm_object_file {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_vmw_shader_type { ____Placeholder_drm_vmw_shader_type } drm_vmw_shader_type ;
struct TYPE_4__ {struct ttm_object_file* tfile; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SVGA3D_INVALID_ID ; 
 int /*<<< orphan*/  SVGA3D_SHADERTYPE_PS ; 
 int /*<<< orphan*/  SVGA3D_SHADERTYPE_VS ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
#define  drm_vmw_shader_type_ps 129 
#define  drm_vmw_shader_type_vs 128 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 TYPE_2__* vmw_fpriv (struct drm_file*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int vmw_user_bo_lookup (struct ttm_object_file*,int /*<<< orphan*/ ,struct vmw_buffer_object**,int /*<<< orphan*/ *) ; 
 int vmw_user_shader_alloc (struct vmw_private*,struct vmw_buffer_object*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_object_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_shader_define(struct drm_device *dev, struct drm_file *file_priv,
			     enum drm_vmw_shader_type shader_type_drm,
			     u32 buffer_handle, size_t size, size_t offset,
			     uint8_t num_input_sig, uint8_t num_output_sig,
			     uint32_t *shader_handle)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct vmw_buffer_object *buffer = NULL;
	SVGA3dShaderType shader_type;
	int ret;

	if (buffer_handle != SVGA3D_INVALID_ID) {
		ret = vmw_user_bo_lookup(tfile, buffer_handle,
					     &buffer, NULL);
		if (unlikely(ret != 0)) {
			VMW_DEBUG_USER("Couldn't find buffer for shader creation.\n");
			return ret;
		}

		if ((u64)buffer->base.num_pages * PAGE_SIZE <
		    (u64)size + (u64)offset) {
			VMW_DEBUG_USER("Illegal buffer- or shader size.\n");
			ret = -EINVAL;
			goto out_bad_arg;
		}
	}

	switch (shader_type_drm) {
	case drm_vmw_shader_type_vs:
		shader_type = SVGA3D_SHADERTYPE_VS;
		break;
	case drm_vmw_shader_type_ps:
		shader_type = SVGA3D_SHADERTYPE_PS;
		break;
	default:
		VMW_DEBUG_USER("Illegal shader type.\n");
		ret = -EINVAL;
		goto out_bad_arg;
	}

	ret = ttm_read_lock(&dev_priv->reservation_sem, true);
	if (unlikely(ret != 0))
		goto out_bad_arg;

	ret = vmw_user_shader_alloc(dev_priv, buffer, size, offset,
				    shader_type, num_input_sig,
				    num_output_sig, tfile, shader_handle);

	ttm_read_unlock(&dev_priv->reservation_sem);
out_bad_arg:
	vmw_bo_unreference(&buffer);
	return ret;
}