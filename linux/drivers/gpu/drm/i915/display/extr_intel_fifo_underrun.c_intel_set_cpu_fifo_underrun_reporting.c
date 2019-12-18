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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  drm; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int __intel_set_cpu_fifo_underrun_reporting (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool intel_set_cpu_fifo_underrun_reporting(struct drm_i915_private *dev_priv,
					   enum pipe pipe, bool enable)
{
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(&dev_priv->irq_lock, flags);
	ret = __intel_set_cpu_fifo_underrun_reporting(&dev_priv->drm, pipe,
						      enable);
	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);

	return ret;
}