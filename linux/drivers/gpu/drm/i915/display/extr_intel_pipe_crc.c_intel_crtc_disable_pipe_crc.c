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
struct intel_pipe_crc {int /*<<< orphan*/  lock; int /*<<< orphan*/  skipped; } ;
struct drm_crtc {size_t index; int /*<<< orphan*/  dev; } ;
struct intel_crtc {struct drm_crtc base; } ;
struct drm_i915_private {struct intel_pipe_crc* pipe_crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  PIPE_CRC_CTL (size_t) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_synchronize_irq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_crtc_disable_pipe_crc(struct intel_crtc *intel_crtc)
{
	struct drm_crtc *crtc = &intel_crtc->base;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_pipe_crc *pipe_crc = &dev_priv->pipe_crc[crtc->index];

	/* Swallow crc's until we stop generating them. */
	spin_lock_irq(&pipe_crc->lock);
	pipe_crc->skipped = INT_MIN;
	spin_unlock_irq(&pipe_crc->lock);

	I915_WRITE(PIPE_CRC_CTL(crtc->index), 0);
	POSTING_READ(PIPE_CRC_CTL(crtc->index));
	intel_synchronize_irq(dev_priv);
}