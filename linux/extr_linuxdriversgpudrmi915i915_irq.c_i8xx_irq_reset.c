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
 int /*<<< orphan*/  GEN2_IRQ_RESET () ; 
 int /*<<< orphan*/  HWSTAM ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i9xx_pipestat_irq_reset (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i8xx_irq_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	i9xx_pipestat_irq_reset(dev_priv);

	I915_WRITE16(HWSTAM, 0xffff);

	GEN2_IRQ_RESET();
}