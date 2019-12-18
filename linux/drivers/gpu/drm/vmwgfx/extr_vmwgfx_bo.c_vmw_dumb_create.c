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
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct vmw_buffer_object {int dummy; } ;
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfile; } ;

/* Variables and functions */
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int vmw_user_bo_alloc (struct vmw_private*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,struct vmw_buffer_object**,int /*<<< orphan*/ *) ; 

int vmw_dumb_create(struct drm_file *file_priv,
		    struct drm_device *dev,
		    struct drm_mode_create_dumb *args)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_buffer_object *vbo;
	int ret;

	args->pitch = args->width * ((args->bpp + 7) / 8);
	args->size = args->pitch * args->height;

	ret = ttm_read_lock(&dev_priv->reservation_sem, true);
	if (unlikely(ret != 0))
		return ret;

	ret = vmw_user_bo_alloc(dev_priv, vmw_fpriv(file_priv)->tfile,
				    args->size, false, &args->handle,
				    &vbo, NULL);
	if (unlikely(ret != 0))
		goto out_no_bo;

	vmw_bo_unreference(&vbo);
out_no_bo:
	ttm_read_unlock(&dev_priv->reservation_sem);
	return ret;
}