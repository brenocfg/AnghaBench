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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct udl_gem_object {int /*<<< orphan*/  base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct udl_gem_object*) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udl_gem_object* udl_gem_alloc_object (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udl_gem_create(struct drm_file *file,
	       struct drm_device *dev,
	       uint64_t size,
	       uint32_t *handle_p)
{
	struct udl_gem_object *obj;
	int ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);

	obj = udl_gem_alloc_object(dev, size);
	if (obj == NULL)
		return -ENOMEM;

	ret = drm_gem_handle_create(file, &obj->base, &handle);
	if (ret) {
		drm_gem_object_release(&obj->base);
		kfree(obj);
		return ret;
	}

	drm_gem_object_put_unlocked(&obj->base);
	*handle_p = handle;
	return 0;
}