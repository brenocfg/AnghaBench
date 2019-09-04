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
struct TYPE_2__ {int /*<<< orphan*/  active_requests; } ;
struct drm_i915_private {TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_gem_park (struct drm_i915_private*) ; 

__attribute__((used)) static void unreserve_gt(struct drm_i915_private *i915)
{
	GEM_BUG_ON(!i915->gt.active_requests);
	if (!--i915->gt.active_requests)
		i915_gem_park(i915);
}