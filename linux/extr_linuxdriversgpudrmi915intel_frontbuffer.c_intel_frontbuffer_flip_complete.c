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
struct TYPE_2__ {unsigned int flip_bits; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ fb_tracking; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORIGIN_FLIP ; 
 int /*<<< orphan*/  intel_frontbuffer_flush (struct drm_i915_private*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void intel_frontbuffer_flip_complete(struct drm_i915_private *dev_priv,
				     unsigned frontbuffer_bits)
{
	spin_lock(&dev_priv->fb_tracking.lock);
	/* Mask any cancelled flips. */
	frontbuffer_bits &= dev_priv->fb_tracking.flip_bits;
	dev_priv->fb_tracking.flip_bits &= ~frontbuffer_bits;
	spin_unlock(&dev_priv->fb_tracking.lock);

	if (frontbuffer_bits)
		intel_frontbuffer_flush(dev_priv,
					frontbuffer_bits, ORIGIN_FLIP);
}