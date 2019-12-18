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
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
i915_hotplug_interrupt_update_locked(struct drm_i915_private *dev_priv,
				     u32 mask,
				     u32 bits)
{
	u32 val;

	lockdep_assert_held(&dev_priv->irq_lock);
	WARN_ON(bits & ~mask);

	val = I915_READ(PORT_HOTPLUG_EN);
	val &= ~mask;
	val |= bits;
	I915_WRITE(PORT_HOTPLUG_EN, val);
}