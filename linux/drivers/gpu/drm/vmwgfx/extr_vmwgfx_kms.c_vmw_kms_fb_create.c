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
struct vmw_surface {int dummy; } ;
struct vmw_private {int capabilities; int /*<<< orphan*/  texture_max_height; int /*<<< orphan*/  texture_max_width; } ;
struct drm_framebuffer {int dummy; } ;
struct vmw_framebuffer {struct drm_framebuffer base; struct ttm_base_object* user_obj; } ;
struct vmw_buffer_object {int dummy; } ;
struct ttm_object_file {int dummy; } ;
struct ttm_base_object {int dummy; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * handles; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOENT ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct vmw_framebuffer*) ; 
 int PTR_ERR (struct vmw_framebuffer*) ; 
 int SVGA_CAP_3D ; 
 struct ttm_base_object* ttm_base_object_lookup (struct ttm_object_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_base_object_unref (struct ttm_base_object**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 
 struct vmw_framebuffer* vmw_kms_new_framebuffer (struct vmw_private*,struct vmw_buffer_object*,struct vmw_surface*,int,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  vmw_kms_srf_ok (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_surface_unreference (struct vmw_surface**) ; 
 int vmw_user_lookup_handle (struct vmw_private*,struct ttm_object_file*,int /*<<< orphan*/ ,struct vmw_surface**,struct vmw_buffer_object**) ; 

__attribute__((used)) static struct drm_framebuffer *vmw_kms_fb_create(struct drm_device *dev,
						 struct drm_file *file_priv,
						 const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct vmw_framebuffer *vfb = NULL;
	struct vmw_surface *surface = NULL;
	struct vmw_buffer_object *bo = NULL;
	struct ttm_base_object *user_obj;
	int ret;

	/*
	 * Take a reference on the user object of the resource
	 * backing the kms fb. This ensures that user-space handle
	 * lookups on that resource will always work as long as
	 * it's registered with a kms framebuffer. This is important,
	 * since vmw_execbuf_process identifies resources in the
	 * command stream using user-space handles.
	 */

	user_obj = ttm_base_object_lookup(tfile, mode_cmd->handles[0]);
	if (unlikely(user_obj == NULL)) {
		DRM_ERROR("Could not locate requested kms frame buffer.\n");
		return ERR_PTR(-ENOENT);
	}

	/**
	 * End conditioned code.
	 */

	/* returns either a bo or surface */
	ret = vmw_user_lookup_handle(dev_priv, tfile,
				     mode_cmd->handles[0],
				     &surface, &bo);
	if (ret)
		goto err_out;


	if (!bo &&
	    !vmw_kms_srf_ok(dev_priv, mode_cmd->width, mode_cmd->height)) {
		DRM_ERROR("Surface size cannot exceed %dx%d",
			dev_priv->texture_max_width,
			dev_priv->texture_max_height);
		goto err_out;
	}


	vfb = vmw_kms_new_framebuffer(dev_priv, bo, surface,
				      !(dev_priv->capabilities & SVGA_CAP_3D),
				      mode_cmd);
	if (IS_ERR(vfb)) {
		ret = PTR_ERR(vfb);
		goto err_out;
 	}

err_out:
	/* vmw_user_lookup_handle takes one ref so does new_fb */
	if (bo)
		vmw_bo_unreference(&bo);
	if (surface)
		vmw_surface_unreference(&surface);

	if (ret) {
		DRM_ERROR("failed to create vmw_framebuffer: %i\n", ret);
		ttm_base_object_unref(&user_obj);
		return ERR_PTR(ret);
	} else
		vfb->user_obj = user_obj;

	return &vfb->base;
}