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
struct v3d_dev {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  mm; } ;
struct drm_gem_object {int size; } ;
struct v3d_bo {int /*<<< orphan*/  node; int /*<<< orphan*/  lock; int /*<<< orphan*/  unref_head; int /*<<< orphan*/  vmas; struct drm_gem_object base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct v3d_bo* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GMP_GRANULARITY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_object_init (struct drm_device*,struct drm_gem_object*,size_t) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int drm_mm_insert_node_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v3d_bo*) ; 
 struct v3d_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 size_t roundup (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 

__attribute__((used)) static struct v3d_bo *v3d_bo_create_struct(struct drm_device *dev,
					   size_t unaligned_size)
{
	struct v3d_dev *v3d = to_v3d_dev(dev);
	struct drm_gem_object *obj;
	struct v3d_bo *bo;
	size_t size = roundup(unaligned_size, PAGE_SIZE);
	int ret;

	if (size == 0)
		return ERR_PTR(-EINVAL);

	bo = kzalloc(sizeof(*bo), GFP_KERNEL);
	if (!bo)
		return ERR_PTR(-ENOMEM);
	obj = &bo->base;

	INIT_LIST_HEAD(&bo->vmas);
	INIT_LIST_HEAD(&bo->unref_head);
	mutex_init(&bo->lock);

	ret = drm_gem_object_init(dev, obj, size);
	if (ret)
		goto free_bo;

	spin_lock(&v3d->mm_lock);
	ret = drm_mm_insert_node_generic(&v3d->mm, &bo->node,
					 obj->size >> PAGE_SHIFT,
					 GMP_GRANULARITY >> PAGE_SHIFT, 0, 0);
	spin_unlock(&v3d->mm_lock);
	if (ret)
		goto free_obj;

	return bo;

free_obj:
	drm_gem_object_release(obj);
free_bo:
	kfree(bo);
	return ERR_PTR(ret);
}