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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_PIPE_VBLANK (unsigned int) ; 
 int /*<<< orphan*/  DE_PIPE_VBLANK_IVB (unsigned int) ; 
 scalar_t__ HAS_PSR (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  drm_vblank_restore (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  ilk_enable_display_irq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int ironlake_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	unsigned long irqflags;
	uint32_t bit = INTEL_GEN(dev_priv) >= 7 ?
		DE_PIPE_VBLANK_IVB(pipe) : DE_PIPE_VBLANK(pipe);

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	ilk_enable_display_irq(dev_priv, bit);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);

	/* Even though there is no DMC, frame counter can get stuck when
	 * PSR is active as no frames are generated.
	 */
	if (HAS_PSR(dev_priv))
		drm_vblank_restore(dev, pipe);

	return 0;
}