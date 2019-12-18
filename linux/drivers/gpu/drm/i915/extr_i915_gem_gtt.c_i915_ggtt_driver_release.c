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
struct pagevec {scalar_t__ nr; int /*<<< orphan*/  pages; } ;
struct TYPE_3__ {struct pagevec pvec; } ;
struct TYPE_4__ {TYPE_1__ wc_stash; } ;
struct drm_i915_private {TYPE_2__ mm; int /*<<< orphan*/  ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  fini_aliasing_ppgtt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ggtt_cleanup_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_cleanup_stolen (struct drm_i915_private*) ; 
 int /*<<< orphan*/  set_pages_array_wb (int /*<<< orphan*/ ,scalar_t__) ; 

void i915_ggtt_driver_release(struct drm_i915_private *i915)
{
	struct pagevec *pvec;

	fini_aliasing_ppgtt(&i915->ggtt);

	ggtt_cleanup_hw(&i915->ggtt);

	pvec = &i915->mm.wc_stash.pvec;
	if (pvec->nr) {
		set_pages_array_wb(pvec->pages, pvec->nr);
		__pagevec_release(pvec);
	}

	i915_gem_cleanup_stolen(i915);
}