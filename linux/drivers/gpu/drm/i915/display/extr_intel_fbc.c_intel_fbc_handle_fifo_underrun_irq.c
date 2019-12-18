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
struct intel_fbc {int /*<<< orphan*/  underrun_work; int /*<<< orphan*/  underrun_detected; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void intel_fbc_handle_fifo_underrun_irq(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	/* There's no guarantee that underrun_detected won't be set to true
	 * right after this check and before the work is scheduled, but that's
	 * not a problem since we'll check it again under the work function
	 * while FBC is locked. This check here is just to prevent us from
	 * unnecessarily scheduling the work, and it relies on the fact that we
	 * never switch underrun_detect back to false after it's true. */
	if (READ_ONCE(fbc->underrun_detected))
		return;

	schedule_work(&fbc->underrun_work);
}