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
struct intel_rps {int gpll_ref_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 

__attribute__((used)) static int byt_gpu_freq(struct drm_i915_private *dev_priv, int val)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	/*
	 * N = val - 0xb7
	 * Slow = Fast = GPLL ref * N
	 */
	return DIV_ROUND_CLOSEST(rps->gpll_ref_freq * (val - 0xb7), 1000);
}