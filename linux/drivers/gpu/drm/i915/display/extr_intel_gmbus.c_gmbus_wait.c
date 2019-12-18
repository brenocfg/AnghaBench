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
struct drm_i915_private {int /*<<< orphan*/  gmbus_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GMBUS2 ; 
 int /*<<< orphan*/  GMBUS4 ; 
 int GMBUS_SATOER ; 
 int /*<<< orphan*/  HAS_GMBUS_IRQ (struct drm_i915_private*) ; 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int wait_for (int,int) ; 
 int wait_for_us (int,int) ; 

__attribute__((used)) static int gmbus_wait(struct drm_i915_private *dev_priv, u32 status, u32 irq_en)
{
	DEFINE_WAIT(wait);
	u32 gmbus2;
	int ret;

	/* Important: The hw handles only the first bit, so set only one! Since
	 * we also need to check for NAKs besides the hw ready/idle signal, we
	 * need to wake up periodically and check that ourselves.
	 */
	if (!HAS_GMBUS_IRQ(dev_priv))
		irq_en = 0;

	add_wait_queue(&dev_priv->gmbus_wait_queue, &wait);
	I915_WRITE_FW(GMBUS4, irq_en);

	status |= GMBUS_SATOER;
	ret = wait_for_us((gmbus2 = I915_READ_FW(GMBUS2)) & status, 2);
	if (ret)
		ret = wait_for((gmbus2 = I915_READ_FW(GMBUS2)) & status, 50);

	I915_WRITE_FW(GMBUS4, 0);
	remove_wait_queue(&dev_priv->gmbus_wait_queue, &wait);

	if (gmbus2 & GMBUS_SATOER)
		return -ENXIO;

	return ret;
}