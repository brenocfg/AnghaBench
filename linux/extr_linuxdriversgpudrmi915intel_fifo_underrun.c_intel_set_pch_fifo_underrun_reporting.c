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
struct intel_crtc {int pch_fifo_underrun_disabled; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  drm; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cpt_set_fifo_underrun_reporting (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  ibx_set_fifo_underrun_reporting (int /*<<< orphan*/ *,int,int) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool intel_set_pch_fifo_underrun_reporting(struct drm_i915_private *dev_priv,
					   enum pipe pch_transcoder,
					   bool enable)
{
	struct intel_crtc *crtc =
		intel_get_crtc_for_pipe(dev_priv, pch_transcoder);
	unsigned long flags;
	bool old;

	/*
	 * NOTE: Pre-LPT has a fixed cpu pipe -> pch transcoder mapping, but LPT
	 * has only one pch transcoder A that all pipes can use. To avoid racy
	 * pch transcoder -> pipe lookups from interrupt code simply store the
	 * underrun statistics in crtc A. Since we never expose this anywhere
	 * nor use it outside of the fifo underrun code here using the "wrong"
	 * crtc on LPT won't cause issues.
	 */

	spin_lock_irqsave(&dev_priv->irq_lock, flags);

	old = !crtc->pch_fifo_underrun_disabled;
	crtc->pch_fifo_underrun_disabled = !enable;

	if (HAS_PCH_IBX(dev_priv))
		ibx_set_fifo_underrun_reporting(&dev_priv->drm,
						pch_transcoder,
						enable);
	else
		cpt_set_fifo_underrun_reporting(&dev_priv->drm,
						pch_transcoder,
						enable, old);

	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);
	return old;
}