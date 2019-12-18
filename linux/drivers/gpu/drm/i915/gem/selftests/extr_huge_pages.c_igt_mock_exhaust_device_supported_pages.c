#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int sg; } ;
struct TYPE_6__ {unsigned int size; } ;
struct i915_vma {TYPE_2__ page_sizes; TYPE_1__ base; } ;
struct TYPE_9__ {struct drm_i915_private* i915; } ;
struct i915_ppgtt {TYPE_4__ vm; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {TYPE_2__ page_sizes; TYPE_1__ base; } ;
struct TYPE_10__ {unsigned int page_sizes; } ;
struct TYPE_8__ {unsigned int page_sizes; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int BIT (int) ; 
 int EINVAL ; 
 TYPE_5__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* fake_huge_pages_object (struct drm_i915_private*,unsigned int,int) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int igt_check_page_sizes (struct i915_vma*) ; 
 TYPE_3__* mkwrite_device_info (struct drm_i915_private*) ; 
 unsigned int* page_sizes ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int igt_mock_exhaust_device_supported_pages(void *arg)
{
	struct i915_ppgtt *ppgtt = arg;
	struct drm_i915_private *i915 = ppgtt->vm.i915;
	unsigned int saved_mask = INTEL_INFO(i915)->page_sizes;
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	int i, j, single;
	int err;

	/*
	 * Sanity check creating objects with every valid page support
	 * combination for our mock device.
	 */

	for (i = 1; i < BIT(ARRAY_SIZE(page_sizes)); i++) {
		unsigned int combination = 0;

		for (j = 0; j < ARRAY_SIZE(page_sizes); j++) {
			if (i & BIT(j))
				combination |= page_sizes[j];
		}

		mkwrite_device_info(i915)->page_sizes = combination;

		for (single = 0; single <= 1; ++single) {
			obj = fake_huge_pages_object(i915, combination, !!single);
			if (IS_ERR(obj)) {
				err = PTR_ERR(obj);
				goto out_device;
			}

			if (obj->base.size != combination) {
				pr_err("obj->base.size=%zu, expected=%u\n",
				       obj->base.size, combination);
				err = -EINVAL;
				goto out_put;
			}

			vma = i915_vma_instance(obj, &ppgtt->vm, NULL);
			if (IS_ERR(vma)) {
				err = PTR_ERR(vma);
				goto out_put;
			}

			err = i915_vma_pin(vma, 0, 0, PIN_USER);
			if (err)
				goto out_close;

			err = igt_check_page_sizes(vma);

			if (vma->page_sizes.sg != combination) {
				pr_err("page_sizes.sg=%u, expected=%u\n",
				       vma->page_sizes.sg, combination);
				err = -EINVAL;
			}

			i915_vma_unpin(vma);
			i915_vma_close(vma);

			i915_gem_object_put(obj);

			if (err)
				goto out_device;
		}
	}

	goto out_device;

out_close:
	i915_vma_close(vma);
out_put:
	i915_gem_object_put(obj);
out_device:
	mkwrite_device_info(i915)->page_sizes = saved_mask;

	return err;
}