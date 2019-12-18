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
struct vc4_file {int dummy; } ;
struct vc4_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct vc4_bo {TYPE_1__ base; int /*<<< orphan*/  madv; } ;
struct drm_vc4_create_bo {int /*<<< orphan*/  handle; int /*<<< orphan*/  size; } ;
struct drm_file {struct vc4_file* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vc4_bo*) ; 
 int PTR_ERR (struct vc4_bo*) ; 
 int /*<<< orphan*/  VC4_BO_TYPE_V3D ; 
 int /*<<< orphan*/  VC4_MADV_WILLNEED ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 struct vc4_bo* vc4_bo_create (struct drm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vc4_grab_bin_bo (struct vc4_dev*,struct vc4_file*) ; 

int vc4_create_bo_ioctl(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_vc4_create_bo *args = data;
	struct vc4_file *vc4file = file_priv->driver_priv;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_bo *bo = NULL;
	int ret;

	ret = vc4_grab_bin_bo(vc4, vc4file);
	if (ret)
		return ret;

	/*
	 * We can't allocate from the BO cache, because the BOs don't
	 * get zeroed, and that might leak data between users.
	 */
	bo = vc4_bo_create(dev, args->size, false, VC4_BO_TYPE_V3D);
	if (IS_ERR(bo))
		return PTR_ERR(bo);

	bo->madv = VC4_MADV_WILLNEED;

	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);
	drm_gem_object_put_unlocked(&bo->base.base);

	return ret;
}