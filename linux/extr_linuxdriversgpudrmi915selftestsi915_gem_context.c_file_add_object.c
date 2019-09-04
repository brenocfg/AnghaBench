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
struct TYPE_2__ {int /*<<< orphan*/  handle_count; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct drm_file {int /*<<< orphan*/  object_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i915_gem_object_get (struct drm_i915_gem_object*) ; 
 int idr_alloc (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_add_object(struct drm_file *file,
			    struct drm_i915_gem_object *obj)
{
	int err;

	GEM_BUG_ON(obj->base.handle_count);

	/* tie the object to the drm_file for easy reaping */
	err = idr_alloc(&file->object_idr, &obj->base, 1, 0, GFP_KERNEL);
	if (err < 0)
		return  err;

	i915_gem_object_get(obj);
	obj->base.handle_count++;
	return 0;
}