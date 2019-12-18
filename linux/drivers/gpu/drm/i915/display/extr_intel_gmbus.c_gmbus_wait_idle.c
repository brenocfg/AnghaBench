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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int /*<<< orphan*/  gmbus_wait_queue; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMBUS2 ; 
 int /*<<< orphan*/  GMBUS4 ; 
 int /*<<< orphan*/  GMBUS_ACTIVE ; 
 scalar_t__ GMBUS_IDLE_EN ; 
 scalar_t__ HAS_GMBUS_IRQ (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int intel_wait_for_register_fw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int
gmbus_wait_idle(struct drm_i915_private *dev_priv)
{
	DEFINE_WAIT(wait);
	u32 irq_enable;
	int ret;

	/* Important: The hw handles only the first bit, so set only one! */
	irq_enable = 0;
	if (HAS_GMBUS_IRQ(dev_priv))
		irq_enable = GMBUS_IDLE_EN;

	add_wait_queue(&dev_priv->gmbus_wait_queue, &wait);
	I915_WRITE_FW(GMBUS4, irq_enable);

	ret = intel_wait_for_register_fw(&dev_priv->uncore,
					 GMBUS2, GMBUS_ACTIVE, 0,
					 10);

	I915_WRITE_FW(GMBUS4, 0);
	remove_wait_queue(&dev_priv->gmbus_wait_queue, &wait);

	return ret;
}