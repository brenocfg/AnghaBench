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
struct lima_device {int /*<<< orphan*/  ddev; } ;
struct lima_bo {int /*<<< orphan*/  gem; int /*<<< orphan*/  va; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct lima_bo* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int drm_gem_object_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lima_bo*) ; 
 struct lima_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lima_bo *lima_bo_create_struct(struct lima_device *dev, u32 size, u32 flags)
{
	struct lima_bo *bo;
	int err;

	size = PAGE_ALIGN(size);

	bo = kzalloc(sizeof(*bo), GFP_KERNEL);
	if (!bo)
		return ERR_PTR(-ENOMEM);

	mutex_init(&bo->lock);
	INIT_LIST_HEAD(&bo->va);

	err = drm_gem_object_init(dev->ddev, &bo->gem, size);
	if (err) {
		kfree(bo);
		return ERR_PTR(err);
	}

	return bo;
}