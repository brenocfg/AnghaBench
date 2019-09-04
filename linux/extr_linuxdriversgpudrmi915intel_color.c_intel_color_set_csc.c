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
struct TYPE_4__ {int /*<<< orphan*/  (* load_csc_matrix ) (struct drm_crtc_state*) ;} ;
struct drm_i915_private {TYPE_2__ display; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {TYPE_1__* crtc; } ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_color_set_csc(struct drm_crtc_state *crtc_state)
{
	struct drm_device *dev = crtc_state->crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (dev_priv->display.load_csc_matrix)
		dev_priv->display.load_csc_matrix(crtc_state);
}