#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int busy_frontbuffer_bits; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  active; scalar_t__ psr2_enabled; int /*<<< orphan*/  enabled; } ;
struct drm_i915_private {TYPE_3__ psr; } ;
struct drm_crtc {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;
struct TYPE_6__ {struct drm_crtc* crtc; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct TYPE_10__ {TYPE_2__ base; } ;
struct TYPE_9__ {int pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  CURSURFLIVE (int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int INTEL_FRONTBUFFER_ALL_MASK (int) ; 
 int ORIGIN_FLIP ; 
 TYPE_5__* dp_to_dig_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_psr_exit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_4__* to_intel_crtc (struct drm_crtc*) ; 

void intel_psr_flush(struct drm_i915_private *dev_priv,
		     unsigned frontbuffer_bits, enum fb_op_origin origin)
{
	struct drm_crtc *crtc;
	enum pipe pipe;

	if (!CAN_PSR(dev_priv))
		return;

	if (origin == ORIGIN_FLIP)
		return;

	mutex_lock(&dev_priv->psr.lock);
	if (!dev_priv->psr.enabled) {
		mutex_unlock(&dev_priv->psr.lock);
		return;
	}

	crtc = dp_to_dig_port(dev_priv->psr.enabled)->base.base.crtc;
	pipe = to_intel_crtc(crtc)->pipe;

	frontbuffer_bits &= INTEL_FRONTBUFFER_ALL_MASK(pipe);
	dev_priv->psr.busy_frontbuffer_bits &= ~frontbuffer_bits;

	/* By definition flush = invalidate + flush */
	if (frontbuffer_bits) {
		if (dev_priv->psr.psr2_enabled) {
			intel_psr_exit(dev_priv);
		} else {
			/*
			 * Display WA #0884: all
			 * This documented WA for bxt can be safely applied
			 * broadly so we can force HW tracking to exit PSR
			 * instead of disabling and re-enabling.
			 * Workaround tells us to write 0 to CUR_SURFLIVE_A,
			 * but it makes more sense write to the current active
			 * pipe.
			 */
			I915_WRITE(CURSURFLIVE(pipe), 0);
		}
	}

	if (!dev_priv->psr.active && !dev_priv->psr.busy_frontbuffer_bits)
		schedule_work(&dev_priv->psr.work);
	mutex_unlock(&dev_priv->psr.lock);
}