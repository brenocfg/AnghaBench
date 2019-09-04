#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ size; } ;
struct i915_vma {scalar_t__ size; scalar_t__ pages; TYPE_3__* obj; TYPE_4__ ggtt_view; TYPE_1__ node; } ;
struct i915_ggtt_view {scalar_t__ type; } ;
struct TYPE_6__ {scalar_t__ pages; } ;
struct TYPE_7__ {TYPE_2__ mm; } ;

/* Variables and functions */
 scalar_t__ I915_GGTT_VIEW_NORMAL ; 
 scalar_t__ memcmp (TYPE_4__*,struct i915_ggtt_view*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static bool assert_pin(struct i915_vma *vma,
		       struct i915_ggtt_view *view,
		       u64 size,
		       const char *name)
{
	bool ok = true;

	if (vma->size != size) {
		pr_err("(%s) VMA is wrong size, expected %llu, found %llu\n",
		       name, size, vma->size);
		ok = false;
	}

	if (vma->node.size < vma->size) {
		pr_err("(%s) VMA binding too small, expected %llu, found %llu\n",
		       name, vma->size, vma->node.size);
		ok = false;
	}

	if (view && view->type != I915_GGTT_VIEW_NORMAL) {
		if (memcmp(&vma->ggtt_view, view, sizeof(*view))) {
			pr_err("(%s) VMA mismatch upon creation!\n",
			       name);
			ok = false;
		}

		if (vma->pages == vma->obj->mm.pages) {
			pr_err("(%s) VMA using original object pages!\n",
			       name);
			ok = false;
		}
	} else {
		if (vma->ggtt_view.type != I915_GGTT_VIEW_NORMAL) {
			pr_err("Not the normal ggtt view! Found %d\n",
			       vma->ggtt_view.type);
			ok = false;
		}

		if (vma->pages != vma->obj->mm.pages) {
			pr_err("VMA not using object pages!\n");
			ok = false;
		}
	}

	return ok;
}