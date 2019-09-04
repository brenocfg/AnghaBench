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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  base; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct drm_i915_gem_object*) ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* i915_gem_object_create (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_gem_create(struct drm_file *file,
		struct drm_i915_private *dev_priv,
		uint64_t size,
		uint32_t *handle_p)
{
	struct drm_i915_gem_object *obj;
	int ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);
	if (size == 0)
		return -EINVAL;

	/* Allocate the new object */
	obj = i915_gem_object_create(dev_priv, size);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

	ret = drm_gem_handle_create(file, &obj->base, &handle);
	/* drop reference from allocate - handle holds it now */
	i915_gem_object_put(obj);
	if (ret)
		return ret;

	*handle_p = handle;
	return 0;
}