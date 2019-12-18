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
struct intel_fbc {unsigned int busy_bits; int /*<<< orphan*/  lock; scalar_t__ enabled; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 int ORIGIN_FLIP ; 
 int ORIGIN_GTT ; 
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_deactivate (struct drm_i915_private*,char*) ; 
 unsigned int intel_fbc_get_frontbuffer_bit (struct intel_fbc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_fbc_invalidate(struct drm_i915_private *dev_priv,
			  unsigned int frontbuffer_bits,
			  enum fb_op_origin origin)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	if (origin == ORIGIN_GTT || origin == ORIGIN_FLIP)
		return;

	mutex_lock(&fbc->lock);

	fbc->busy_bits |= intel_fbc_get_frontbuffer_bit(fbc) & frontbuffer_bits;

	if (fbc->enabled && fbc->busy_bits)
		intel_fbc_deactivate(dev_priv, "frontbuffer write");

	mutex_unlock(&fbc->lock);
}