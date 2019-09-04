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
struct drm_i915_private {unsigned int irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPINVGTT ; 
 int /*<<< orphan*/  DPINVGTT_STATUS_MASK ; 
 int /*<<< orphan*/  DPINVGTT_STATUS_MASK_CHV ; 
 int /*<<< orphan*/  GEN3_IRQ_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 int /*<<< orphan*/  VLV_ ; 
 int /*<<< orphan*/  i915_hotplug_interrupt_update_locked (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i9xx_pipestat_irq_reset (struct drm_i915_private*) ; 

__attribute__((used)) static void vlv_display_irq_reset(struct drm_i915_private *dev_priv)
{
	if (IS_CHERRYVIEW(dev_priv))
		I915_WRITE(DPINVGTT, DPINVGTT_STATUS_MASK_CHV);
	else
		I915_WRITE(DPINVGTT, DPINVGTT_STATUS_MASK);

	i915_hotplug_interrupt_update_locked(dev_priv, 0xffffffff, 0);
	I915_WRITE(PORT_HOTPLUG_STAT, I915_READ(PORT_HOTPLUG_STAT));

	i9xx_pipestat_irq_reset(dev_priv);

	GEN3_IRQ_RESET(VLV_);
	dev_priv->irq_mask = ~0u;
}