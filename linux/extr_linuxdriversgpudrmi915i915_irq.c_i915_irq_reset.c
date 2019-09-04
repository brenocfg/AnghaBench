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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN3_IRQ_RESET () ; 
 int /*<<< orphan*/  HWSTAM ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 int /*<<< orphan*/  i915_hotplug_interrupt_update (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i9xx_pipestat_irq_reset (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i915_irq_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (I915_HAS_HOTPLUG(dev_priv)) {
		i915_hotplug_interrupt_update(dev_priv, 0xffffffff, 0);
		I915_WRITE(PORT_HOTPLUG_STAT, I915_READ(PORT_HOTPLUG_STAT));
	}

	i9xx_pipestat_irq_reset(dev_priv);

	I915_WRITE(HWSTAM, 0xffffffff);

	GEN3_IRQ_RESET();
}