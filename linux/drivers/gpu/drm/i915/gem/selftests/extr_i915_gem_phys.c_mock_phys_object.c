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
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  pages_pin_count; } ;
struct drm_i915_gem_object {TYPE_2__ mm; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int i915_gem_object_attach_phys (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* i915_gem_object_create_shmem (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_phys_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int mock_phys_object(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct drm_i915_gem_object *obj;
	int err;

	/* Create an object and bind it to a contiguous set of physical pages,
	 * i.e. exercise the i915_gem_object_phys API.
	 */

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	if (IS_ERR(obj)) {
		err = PTR_ERR(obj);
		pr_err("i915_gem_object_create failed, err=%d\n", err);
		goto out;
	}

	mutex_lock(&i915->drm.struct_mutex);
	err = i915_gem_object_attach_phys(obj, PAGE_SIZE);
	mutex_unlock(&i915->drm.struct_mutex);
	if (err) {
		pr_err("i915_gem_object_attach_phys failed, err=%d\n", err);
		goto out_obj;
	}

	if (obj->ops != &i915_gem_phys_ops) {
		pr_err("i915_gem_object_attach_phys did not create a phys object\n");
		err = -EINVAL;
		goto out_obj;
	}

	if (!atomic_read(&obj->mm.pages_pin_count)) {
		pr_err("i915_gem_object_attach_phys did not pin its phys pages\n");
		err = -EINVAL;
		goto out_obj;
	}

	/* Make the object dirty so that put_pages must do copy back the data */
	i915_gem_object_lock(obj);
	err = i915_gem_object_set_to_gtt_domain(obj, true);
	i915_gem_object_unlock(obj);
	if (err) {
		pr_err("i915_gem_object_set_to_gtt_domain failed with err=%d\n",
		       err);
		goto out_obj;
	}

out_obj:
	i915_gem_object_put(obj);
out:
	return err;
}