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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  gt; int /*<<< orphan*/  ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int ggtt_probe_hw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_vtd_active () ; 

int i915_ggtt_probe_hw(struct drm_i915_private *i915)
{
	int ret;

	ret = ggtt_probe_hw(&i915->ggtt, &i915->gt);
	if (ret)
		return ret;

	if (intel_vtd_active())
		dev_info(i915->drm.dev, "VT-d active for gfx access\n");

	return 0;
}