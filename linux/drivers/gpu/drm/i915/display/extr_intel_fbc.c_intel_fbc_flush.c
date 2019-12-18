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
struct intel_fbc {unsigned int busy_bits; int /*<<< orphan*/  lock; int /*<<< orphan*/  crtc; int /*<<< orphan*/  flip_pending; scalar_t__ active; scalar_t__ enabled; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 int ORIGIN_FLIP ; 
 int ORIGIN_GTT ; 
 int /*<<< orphan*/  __intel_fbc_post_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 unsigned int intel_fbc_get_frontbuffer_bit (struct intel_fbc*) ; 
 int /*<<< orphan*/  intel_fbc_recompress (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_fbc_flush(struct drm_i915_private *dev_priv,
		     unsigned int frontbuffer_bits, enum fb_op_origin origin)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	mutex_lock(&fbc->lock);

	fbc->busy_bits &= ~frontbuffer_bits;

	if (origin == ORIGIN_GTT || origin == ORIGIN_FLIP)
		goto out;

	if (!fbc->busy_bits && fbc->enabled &&
	    (frontbuffer_bits & intel_fbc_get_frontbuffer_bit(fbc))) {
		if (fbc->active)
			intel_fbc_recompress(dev_priv);
		else if (!fbc->flip_pending)
			__intel_fbc_post_update(fbc->crtc);
	}

out:
	mutex_unlock(&fbc->lock);
}