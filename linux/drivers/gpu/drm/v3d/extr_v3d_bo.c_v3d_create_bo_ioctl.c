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
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int start; } ;
struct v3d_bo {TYPE_2__ base; TYPE_1__ node; } ;
struct drm_v3d_create_bo {scalar_t__ flags; int offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  size; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct v3d_bo*) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct v3d_bo*) ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct v3d_bo* v3d_bo_create (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 

int v3d_create_bo_ioctl(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_v3d_create_bo *args = data;
	struct v3d_bo *bo = NULL;
	int ret;

	if (args->flags != 0) {
		DRM_INFO("unknown create_bo flags: %d\n", args->flags);
		return -EINVAL;
	}

	bo = v3d_bo_create(dev, file_priv, PAGE_ALIGN(args->size));
	if (IS_ERR(bo))
		return PTR_ERR(bo);

	args->offset = bo->node.start << PAGE_SHIFT;

	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);
	drm_gem_object_put_unlocked(&bo->base.base);

	return ret;
}