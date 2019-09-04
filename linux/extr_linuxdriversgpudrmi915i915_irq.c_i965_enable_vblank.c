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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_START_VBLANK_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  i915_enable_pipestat (struct drm_i915_private*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i965_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	i915_enable_pipestat(dev_priv, pipe,
			     PIPE_START_VBLANK_INTERRUPT_STATUS);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);

	return 0;
}