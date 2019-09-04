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
struct TYPE_2__ {int irqs_enabled; } ;
struct drm_i915_private {TYPE_1__ runtime_pm; } ;

/* Variables and functions */

__attribute__((used)) static inline bool intel_irqs_enabled(struct drm_i915_private *dev_priv)
{
	/*
	 * We only use drm_irq_uninstall() at unload and VT switch, so
	 * this is the only thing we need to check.
	 */
	return dev_priv->runtime_pm.irqs_enabled;
}