#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_engine_cs {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_engine_flag (struct intel_engine_cs*) ; 
 int intel_gpu_reset (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int intel_gt_reset_engine(struct drm_i915_private *dev_priv,
					struct intel_engine_cs *engine)
{
	return intel_gpu_reset(dev_priv, intel_engine_flag(engine));
}