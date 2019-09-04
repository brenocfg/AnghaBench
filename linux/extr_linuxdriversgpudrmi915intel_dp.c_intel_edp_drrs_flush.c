#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ type; unsigned int busy_frontbuffer_bits; scalar_t__ refresh_rate_type; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; TYPE_9__* dp; } ;
struct drm_i915_private {TYPE_6__ drrs; } ;
struct drm_crtc {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_18__ {TYPE_5__* attached_connector; } ;
struct TYPE_10__ {struct drm_crtc* crtc; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
struct TYPE_17__ {TYPE_2__ base; } ;
struct TYPE_16__ {int pipe; int /*<<< orphan*/  config; } ;
struct TYPE_13__ {TYPE_3__* fixed_mode; } ;
struct TYPE_14__ {TYPE_4__ panel; } ;
struct TYPE_12__ {int /*<<< orphan*/  vrefresh; } ;

/* Variables and functions */
 scalar_t__ DRRS_LOW_RR ; 
 scalar_t__ DRRS_NOT_SUPPORTED ; 
 unsigned int INTEL_FRONTBUFFER_ALL_MASK (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 TYPE_8__* dp_to_dig_port (TYPE_9__*) ; 
 int /*<<< orphan*/  intel_dp_set_drrs_state (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__* to_intel_crtc (struct drm_crtc*) ; 

void intel_edp_drrs_flush(struct drm_i915_private *dev_priv,
			  unsigned int frontbuffer_bits)
{
	struct drm_crtc *crtc;
	enum pipe pipe;

	if (dev_priv->drrs.type == DRRS_NOT_SUPPORTED)
		return;

	cancel_delayed_work(&dev_priv->drrs.work);

	mutex_lock(&dev_priv->drrs.mutex);
	if (!dev_priv->drrs.dp) {
		mutex_unlock(&dev_priv->drrs.mutex);
		return;
	}

	crtc = dp_to_dig_port(dev_priv->drrs.dp)->base.base.crtc;
	pipe = to_intel_crtc(crtc)->pipe;

	frontbuffer_bits &= INTEL_FRONTBUFFER_ALL_MASK(pipe);
	dev_priv->drrs.busy_frontbuffer_bits &= ~frontbuffer_bits;

	/* flush means busy screen hence upclock */
	if (frontbuffer_bits && dev_priv->drrs.refresh_rate_type == DRRS_LOW_RR)
		intel_dp_set_drrs_state(dev_priv, to_intel_crtc(crtc)->config,
				dev_priv->drrs.dp->attached_connector->panel.fixed_mode->vrefresh);

	/*
	 * flush also means no more activity hence schedule downclock, if all
	 * other fbs are quiescent too
	 */
	if (!dev_priv->drrs.busy_frontbuffer_bits)
		schedule_delayed_work(&dev_priv->drrs.work,
				msecs_to_jiffies(1000));
	mutex_unlock(&dev_priv->drrs.mutex);
}