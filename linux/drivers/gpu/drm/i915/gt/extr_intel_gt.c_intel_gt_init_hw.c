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
struct TYPE_2__ {int /*<<< orphan*/ * ggtt; } ;
struct drm_i915_private {int /*<<< orphan*/  ggtt; TYPE_1__ gt; } ;

/* Variables and functions */

void intel_gt_init_hw(struct drm_i915_private *i915)
{
	i915->gt.ggtt = &i915->ggtt;
}