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
struct TYPE_8__ {unsigned int busy_frontbuffer_bits; int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled; } ;
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
 unsigned int INTEL_FRONTBUFFER_ALL_MASK (int) ; 
 int ORIGIN_FLIP ; 
 TYPE_5__* dp_to_dig_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_psr_exit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* to_intel_crtc (struct drm_crtc*) ; 

void intel_psr_invalidate(struct drm_i915_private *dev_priv,
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
	dev_priv->psr.busy_frontbuffer_bits |= frontbuffer_bits;

	if (frontbuffer_bits)
		intel_psr_exit(dev_priv);

	mutex_unlock(&dev_priv->psr.lock);
}