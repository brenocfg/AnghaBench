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
typedef  int /*<<< orphan*/  u32 ;
struct lima_device {int dummy; } ;
struct lima_bo {int /*<<< orphan*/  gem; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct lima_bo*) ; 
 int PTR_ERR (struct lima_bo*) ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct lima_bo* lima_bo_create (struct lima_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lima_device* to_lima_dev (struct drm_device*) ; 

int lima_gem_create_handle(struct drm_device *dev, struct drm_file *file,
			   u32 size, u32 flags, u32 *handle)
{
	int err;
	struct lima_bo *bo;
	struct lima_device *ldev = to_lima_dev(dev);

	bo = lima_bo_create(ldev, size, flags, NULL);
	if (IS_ERR(bo))
		return PTR_ERR(bo);

	err = drm_gem_handle_create(file, &bo->gem, handle);

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(&bo->gem);

	return err;
}