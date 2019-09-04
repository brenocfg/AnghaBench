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
typedef  int /*<<< orphan*/  u64 ;
struct vkms_gem_object {int /*<<< orphan*/  pages_lock; int /*<<< orphan*/  gem; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vkms_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vkms_gem_object*) ; 
 struct vkms_gem_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vkms_gem_object *__vkms_gem_create(struct drm_device *dev,
						 u64 size)
{
	struct vkms_gem_object *obj;
	int ret;

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (!obj)
		return ERR_PTR(-ENOMEM);

	size = roundup(size, PAGE_SIZE);
	ret = drm_gem_object_init(dev, &obj->gem, size);
	if (ret) {
		kfree(obj);
		return ERR_PTR(ret);
	}

	mutex_init(&obj->pages_lock);

	return obj;
}