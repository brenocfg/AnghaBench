#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int busy_frontbuffer_bits; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  active; int /*<<< orphan*/  pipe; int /*<<< orphan*/  enabled; } ;
struct drm_i915_private {TYPE_1__ psr; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 unsigned int INTEL_FRONTBUFFER_ALL_MASK (int /*<<< orphan*/ ) ; 
 int ORIGIN_FLIP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psr_force_hw_tracking_exit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void intel_psr_flush(struct drm_i915_private *dev_priv,
		     unsigned frontbuffer_bits, enum fb_op_origin origin)
{
	if (!CAN_PSR(dev_priv))
		return;

	if (origin == ORIGIN_FLIP)
		return;

	mutex_lock(&dev_priv->psr.lock);
	if (!dev_priv->psr.enabled) {
		mutex_unlock(&dev_priv->psr.lock);
		return;
	}

	frontbuffer_bits &= INTEL_FRONTBUFFER_ALL_MASK(dev_priv->psr.pipe);
	dev_priv->psr.busy_frontbuffer_bits &= ~frontbuffer_bits;

	/* By definition flush = invalidate + flush */
	if (frontbuffer_bits)
		psr_force_hw_tracking_exit(dev_priv);

	if (!dev_priv->psr.active && !dev_priv->psr.busy_frontbuffer_bits)
		schedule_work(&dev_priv->psr.work);
	mutex_unlock(&dev_priv->psr.lock);
}