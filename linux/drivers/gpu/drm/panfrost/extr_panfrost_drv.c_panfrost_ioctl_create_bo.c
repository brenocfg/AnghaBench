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
struct TYPE_2__ {int start; } ;
struct panfrost_gem_object {TYPE_1__ node; } ;
struct drm_panfrost_create_bo {int flags; int offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  size; scalar_t__ pad; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct panfrost_gem_object*) ; 
 int PAGE_SHIFT ; 
 int PANFROST_BO_HEAP ; 
 int PANFROST_BO_NOEXEC ; 
 int PTR_ERR (struct panfrost_gem_object*) ; 
 struct panfrost_gem_object* panfrost_gem_create_with_handle (struct drm_file*,struct drm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panfrost_ioctl_create_bo(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct panfrost_gem_object *bo;
	struct drm_panfrost_create_bo *args = data;

	if (!args->size || args->pad ||
	    (args->flags & ~(PANFROST_BO_NOEXEC | PANFROST_BO_HEAP)))
		return -EINVAL;

	/* Heaps should never be executable */
	if ((args->flags & PANFROST_BO_HEAP) &&
	    !(args->flags & PANFROST_BO_NOEXEC))
		return -EINVAL;

	bo = panfrost_gem_create_with_handle(file, dev, args->size, args->flags,
					     &args->handle);
	if (IS_ERR(bo))
		return PTR_ERR(bo);

	args->offset = bo->node.start << PAGE_SHIFT;

	return 0;
}