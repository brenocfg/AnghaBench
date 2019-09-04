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
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int __igt_reset_evict_vma (struct drm_i915_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igt_reset_evict_ggtt(void *arg)
{
	struct drm_i915_private *i915 = arg;

	return __igt_reset_evict_vma(i915, &i915->ggtt.vm);
}