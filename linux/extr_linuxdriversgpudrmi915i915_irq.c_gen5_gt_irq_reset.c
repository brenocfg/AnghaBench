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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN3_IRQ_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_PM ; 
 int /*<<< orphan*/  GT ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static void gen5_gt_irq_reset(struct drm_i915_private *dev_priv)
{
	GEN3_IRQ_RESET(GT);
	if (INTEL_GEN(dev_priv) >= 6)
		GEN3_IRQ_RESET(GEN6_PM);
}