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
struct intel_rps {int /*<<< orphan*/  gpll_ref_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chv_freq_opcode(struct drm_i915_private *dev_priv, int val)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	/* CHV needs even values */
	return DIV_ROUND_CLOSEST(2 * 1000 * val, rps->gpll_ref_freq) * 2;
}