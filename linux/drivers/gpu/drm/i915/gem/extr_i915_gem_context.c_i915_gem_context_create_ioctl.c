#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_private {int /*<<< orphan*/  gt; } ;
struct drm_i915_gem_context_create_ext {int flags; int ctx_id; int /*<<< orphan*/  extensions; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct create_ext {int /*<<< orphan*/  ctx; int /*<<< orphan*/  fpriv; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_logical_contexts; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_3__* DRIVER_CAPS (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,...) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int I915_CONTEXT_CREATE_FLAGS_UNKNOWN ; 
 int I915_CONTEXT_CREATE_FLAGS_USE_EXTENSIONS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ client_is_banned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_extensions ; 
 TYPE_1__* current ; 
 int gem_context_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_pid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_create_context (struct drm_i915_private*,int) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int i915_user_extensions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct create_ext*) ; 
 int intel_gt_terminally_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

int i915_gem_context_create_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file)
{
	struct drm_i915_private *i915 = to_i915(dev);
	struct drm_i915_gem_context_create_ext *args = data;
	struct create_ext ext_data;
	int ret;

	if (!DRIVER_CAPS(i915)->has_logical_contexts)
		return -ENODEV;

	if (args->flags & I915_CONTEXT_CREATE_FLAGS_UNKNOWN)
		return -EINVAL;

	ret = intel_gt_terminally_wedged(&i915->gt);
	if (ret)
		return ret;

	ext_data.fpriv = file->driver_priv;
	if (client_is_banned(ext_data.fpriv)) {
		DRM_DEBUG("client %s[%d] banned from creating ctx\n",
			  current->comm,
			  pid_nr(get_task_pid(current, PIDTYPE_PID)));
		return -EIO;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	ext_data.ctx = i915_gem_create_context(i915, args->flags);
	mutex_unlock(&dev->struct_mutex);
	if (IS_ERR(ext_data.ctx))
		return PTR_ERR(ext_data.ctx);

	if (args->flags & I915_CONTEXT_CREATE_FLAGS_USE_EXTENSIONS) {
		ret = i915_user_extensions(u64_to_user_ptr(args->extensions),
					   create_extensions,
					   ARRAY_SIZE(create_extensions),
					   &ext_data);
		if (ret)
			goto err_ctx;
	}

	ret = gem_context_register(ext_data.ctx, ext_data.fpriv);
	if (ret < 0)
		goto err_ctx;

	args->ctx_id = ret;
	DRM_DEBUG("HW context %d created\n", args->ctx_id);

	return 0;

err_ctx:
	context_close(ext_data.ctx);
	return ret;
}