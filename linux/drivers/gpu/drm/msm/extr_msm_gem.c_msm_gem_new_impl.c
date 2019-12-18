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
typedef  int uint32_t ;
struct drm_gem_object {int dummy; } ;
struct msm_gem_object {int flags; struct drm_gem_object base; int /*<<< orphan*/  mm_list; int /*<<< orphan*/  vmas; int /*<<< orphan*/  submit_entry; int /*<<< orphan*/  madv; int /*<<< orphan*/  lock; } ;
struct msm_drm_private {int /*<<< orphan*/  inactive_list; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  MSM_BO_CACHED 130 
 int MSM_BO_CACHE_MASK ; 
#define  MSM_BO_UNCACHED 129 
#define  MSM_BO_WC 128 
 int /*<<< orphan*/  MSM_MADV_WILLNEED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct msm_gem_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_gem_new_impl(struct drm_device *dev,
		uint32_t size, uint32_t flags,
		struct drm_gem_object **obj,
		bool struct_mutex_locked)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_gem_object *msm_obj;

	switch (flags & MSM_BO_CACHE_MASK) {
	case MSM_BO_UNCACHED:
	case MSM_BO_CACHED:
	case MSM_BO_WC:
		break;
	default:
		DRM_DEV_ERROR(dev->dev, "invalid cache flag: %x\n",
				(flags & MSM_BO_CACHE_MASK));
		return -EINVAL;
	}

	msm_obj = kzalloc(sizeof(*msm_obj), GFP_KERNEL);
	if (!msm_obj)
		return -ENOMEM;

	mutex_init(&msm_obj->lock);

	msm_obj->flags = flags;
	msm_obj->madv = MSM_MADV_WILLNEED;

	INIT_LIST_HEAD(&msm_obj->submit_entry);
	INIT_LIST_HEAD(&msm_obj->vmas);

	if (struct_mutex_locked) {
		WARN_ON(!mutex_is_locked(&dev->struct_mutex));
		list_add_tail(&msm_obj->mm_list, &priv->inactive_list);
	} else {
		mutex_lock(&dev->struct_mutex);
		list_add_tail(&msm_obj->mm_list, &priv->inactive_list);
		mutex_unlock(&dev->struct_mutex);
	}

	*obj = &msm_obj->base;

	return 0;
}