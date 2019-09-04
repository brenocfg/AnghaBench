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
struct TYPE_7__ {unsigned int sg; unsigned int gtt; int /*<<< orphan*/  phys; } ;
struct i915_vma {TYPE_2__ page_sizes; struct drm_i915_gem_object* obj; TYPE_1__* vm; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_8__ {unsigned int sg; int gtt; int /*<<< orphan*/  phys; } ;
struct TYPE_9__ {TYPE_3__ page_sizes; } ;
struct drm_i915_gem_object {TYPE_4__ mm; } ;
struct TYPE_10__ {unsigned int page_sizes; } ;
struct TYPE_6__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HAS_PAGE_SIZES (struct drm_i915_private*,unsigned int) ; 
 TYPE_5__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static int igt_check_page_sizes(struct i915_vma *vma)
{
	struct drm_i915_private *i915 = vma->vm->i915;
	unsigned int supported = INTEL_INFO(i915)->page_sizes;
	struct drm_i915_gem_object *obj = vma->obj;
	int err = 0;

	if (!HAS_PAGE_SIZES(i915, vma->page_sizes.sg)) {
		pr_err("unsupported page_sizes.sg=%u, supported=%u\n",
		       vma->page_sizes.sg & ~supported, supported);
		err = -EINVAL;
	}

	if (!HAS_PAGE_SIZES(i915, vma->page_sizes.gtt)) {
		pr_err("unsupported page_sizes.gtt=%u, supported=%u\n",
		       vma->page_sizes.gtt & ~supported, supported);
		err = -EINVAL;
	}

	if (vma->page_sizes.phys != obj->mm.page_sizes.phys) {
		pr_err("vma->page_sizes.phys(%u) != obj->mm.page_sizes.phys(%u)\n",
		       vma->page_sizes.phys, obj->mm.page_sizes.phys);
		err = -EINVAL;
	}

	if (vma->page_sizes.sg != obj->mm.page_sizes.sg) {
		pr_err("vma->page_sizes.sg(%u) != obj->mm.page_sizes.sg(%u)\n",
		       vma->page_sizes.sg, obj->mm.page_sizes.sg);
		err = -EINVAL;
	}

	if (obj->mm.page_sizes.gtt) {
		pr_err("obj->page_sizes.gtt(%u) should never be set\n",
		       obj->mm.page_sizes.gtt);
		err = -EINVAL;
	}

	return err;
}