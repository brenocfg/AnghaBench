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
struct vmw_resource {int dummy; } ;
struct vmw_private {struct vmw_overlay* overlay_priv; } ;
struct vmw_overlay {int /*<<< orphan*/  mutex; } ;
struct vmw_buffer_object {int dummy; } ;
struct ttm_object_file {int dummy; } ;
struct drm_vmw_control_stream_arg {int /*<<< orphan*/  handle; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  enabled; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 
 int /*<<< orphan*/  vmw_overlay_available (struct vmw_private*) ; 
 int vmw_overlay_stop (struct vmw_private*,int /*<<< orphan*/ ,int,int) ; 
 int vmw_overlay_update_stream (struct vmw_private*,struct vmw_buffer_object*,struct drm_vmw_control_stream_arg*,int) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 int vmw_user_bo_lookup (struct ttm_object_file*,int /*<<< orphan*/ ,struct vmw_buffer_object**,int /*<<< orphan*/ *) ; 
 int vmw_user_stream_lookup (struct vmw_private*,struct ttm_object_file*,int /*<<< orphan*/ *,struct vmw_resource**) ; 

int vmw_overlay_ioctl(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_overlay *overlay = dev_priv->overlay_priv;
	struct drm_vmw_control_stream_arg *arg =
	    (struct drm_vmw_control_stream_arg *)data;
	struct vmw_buffer_object *buf;
	struct vmw_resource *res;
	int ret;

	if (!vmw_overlay_available(dev_priv))
		return -ENOSYS;

	ret = vmw_user_stream_lookup(dev_priv, tfile, &arg->stream_id, &res);
	if (ret)
		return ret;

	mutex_lock(&overlay->mutex);

	if (!arg->enabled) {
		ret = vmw_overlay_stop(dev_priv, arg->stream_id, false, true);
		goto out_unlock;
	}

	ret = vmw_user_bo_lookup(tfile, arg->handle, &buf, NULL);
	if (ret)
		goto out_unlock;

	ret = vmw_overlay_update_stream(dev_priv, buf, arg, true);

	vmw_bo_unreference(&buf);

out_unlock:
	mutex_unlock(&overlay->mutex);
	vmw_resource_unreference(&res);

	return ret;
}