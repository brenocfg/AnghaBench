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
struct vc4_dev {int /*<<< orphan*/  bo_lock; } ;
struct drm_vc4_label_bo {int /*<<< orphan*/  handle; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char* strndup_user (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_bo_set_label (struct drm_gem_object*,int) ; 
 int vc4_get_user_label (struct vc4_dev*,char*) ; 

int vc4_label_bo_ioctl(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct drm_vc4_label_bo *args = data;
	char *name;
	struct drm_gem_object *gem_obj;
	int ret = 0, label;

	if (!args->len)
		return -EINVAL;

	name = strndup_user(u64_to_user_ptr(args->name), args->len + 1);
	if (IS_ERR(name))
		return PTR_ERR(name);

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	if (!gem_obj) {
		DRM_ERROR("Failed to look up GEM BO %d\n", args->handle);
		kfree(name);
		return -ENOENT;
	}

	mutex_lock(&vc4->bo_lock);
	label = vc4_get_user_label(vc4, name);
	if (label != -1)
		vc4_bo_set_label(gem_obj, label);
	else
		ret = -ENOMEM;
	mutex_unlock(&vc4->bo_lock);

	drm_gem_object_put_unlocked(gem_obj);

	return ret;
}