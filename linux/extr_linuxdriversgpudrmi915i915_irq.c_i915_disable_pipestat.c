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
struct drm_i915_private {int* pipestat_irq_mask; int /*<<< orphan*/  irq_lock; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPESTAT (int) ; 
 int PIPESTAT_INT_STATUS_MASK ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int) ; 
 int i915_pipestat_enable_mask (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_irqs_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

void i915_disable_pipestat(struct drm_i915_private *dev_priv,
			   enum pipe pipe, u32 status_mask)
{
	i915_reg_t reg = PIPESTAT(pipe);
	u32 enable_mask;

	WARN_ONCE(status_mask & ~PIPESTAT_INT_STATUS_MASK,
		  "pipe %c: status_mask=0x%x\n",
		  pipe_name(pipe), status_mask);

	lockdep_assert_held(&dev_priv->irq_lock);
	WARN_ON(!intel_irqs_enabled(dev_priv));

	if ((dev_priv->pipestat_irq_mask[pipe] & status_mask) == 0)
		return;

	dev_priv->pipestat_irq_mask[pipe] &= ~status_mask;
	enable_mask = i915_pipestat_enable_mask(dev_priv, pipe);

	I915_WRITE(reg, enable_mask | status_mask);
	POSTING_READ(reg);
}