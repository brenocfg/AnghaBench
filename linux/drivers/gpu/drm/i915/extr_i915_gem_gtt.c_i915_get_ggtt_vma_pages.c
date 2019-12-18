#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; int /*<<< orphan*/  remapped; int /*<<< orphan*/  rotated; } ;
struct i915_vma {TYPE_4__ ggtt_view; int /*<<< orphan*/ * pages; TYPE_2__* obj; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pages; } ;
struct TYPE_8__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
#define  I915_GGTT_VIEW_NORMAL 131 
#define  I915_GGTT_VIEW_PARTIAL 130 
#define  I915_GGTT_VIEW_REMAPPED 129 
#define  I915_GGTT_VIEW_ROTATED 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_has_pinned_pages (TYPE_2__*) ; 
 int /*<<< orphan*/ * intel_partial_pages (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * intel_remap_pages (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * intel_rotate_pages (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
i915_get_ggtt_vma_pages(struct i915_vma *vma)
{
	int ret;

	/* The vma->pages are only valid within the lifespan of the borrowed
	 * obj->mm.pages. When the obj->mm.pages sg_table is regenerated, so
	 * must be the vma->pages. A simple rule is that vma->pages must only
	 * be accessed when the obj->mm.pages are pinned.
	 */
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(vma->obj));

	switch (vma->ggtt_view.type) {
	default:
		GEM_BUG_ON(vma->ggtt_view.type);
		/* fall through */
	case I915_GGTT_VIEW_NORMAL:
		vma->pages = vma->obj->mm.pages;
		return 0;

	case I915_GGTT_VIEW_ROTATED:
		vma->pages =
			intel_rotate_pages(&vma->ggtt_view.rotated, vma->obj);
		break;

	case I915_GGTT_VIEW_REMAPPED:
		vma->pages =
			intel_remap_pages(&vma->ggtt_view.remapped, vma->obj);
		break;

	case I915_GGTT_VIEW_PARTIAL:
		vma->pages = intel_partial_pages(&vma->ggtt_view, vma->obj);
		break;
	}

	ret = 0;
	if (IS_ERR(vma->pages)) {
		ret = PTR_ERR(vma->pages);
		vma->pages = NULL;
		DRM_ERROR("Failed to get pages for VMA view type %u (%d)!\n",
			  vma->ggtt_view.type, ret);
	}
	return ret;
}