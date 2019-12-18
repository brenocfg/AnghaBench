#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct intel_dsi {TYPE_2__ base; } ;
struct TYPE_7__ {int seq_version; } ;
struct TYPE_8__ {TYPE_3__ dsi; } ;
struct drm_i915_private {TYPE_4__ vbt; } ;

/* Variables and functions */
 scalar_t__ is_vid_mode (struct intel_dsi*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_dsi_msleep(struct intel_dsi *intel_dsi, int msec)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dsi->base.base.dev);

	/* For v3 VBTs in vid-mode the delays are part of the VBT sequences */
	if (is_vid_mode(intel_dsi) && dev_priv->vbt.dsi.seq_version >= 3)
		return;

	msleep(msec);
}