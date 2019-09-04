#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int busy_bits; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_2__ fb_tracking; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 int ORIGIN_CS ; 
 int /*<<< orphan*/  intel_frontbuffer_flush (struct drm_i915_private*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void __intel_fb_obj_flush(struct drm_i915_gem_object *obj,
			  enum fb_op_origin origin,
			  unsigned int frontbuffer_bits)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);

	if (origin == ORIGIN_CS) {
		spin_lock(&dev_priv->fb_tracking.lock);
		/* Filter out new bits since rendering started. */
		frontbuffer_bits &= dev_priv->fb_tracking.busy_bits;
		dev_priv->fb_tracking.busy_bits &= ~frontbuffer_bits;
		spin_unlock(&dev_priv->fb_tracking.lock);
	}

	if (frontbuffer_bits)
		intel_frontbuffer_flush(dev_priv, frontbuffer_bits, origin);
}