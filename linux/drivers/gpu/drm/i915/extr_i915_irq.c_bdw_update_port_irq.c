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
typedef  int u32 ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_DE_PORT_IMR ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  intel_irqs_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bdw_update_port_irq(struct drm_i915_private *dev_priv,
				u32 interrupt_mask,
				u32 enabled_irq_mask)
{
	u32 new_val;
	u32 old_val;

	lockdep_assert_held(&dev_priv->irq_lock);

	WARN_ON(enabled_irq_mask & ~interrupt_mask);

	if (WARN_ON(!intel_irqs_enabled(dev_priv)))
		return;

	old_val = I915_READ(GEN8_DE_PORT_IMR);

	new_val = old_val;
	new_val &= ~interrupt_mask;
	new_val |= (~enabled_irq_mask & interrupt_mask);

	if (new_val != old_val) {
		I915_WRITE(GEN8_DE_PORT_IMR, new_val);
		POSTING_READ(GEN8_DE_PORT_IMR);
	}
}