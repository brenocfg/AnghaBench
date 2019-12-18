#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gma_crtc {int /*<<< orphan*/  active; } ;
struct drm_psb_private {struct drm_crtc** pipe_to_crtc_mapping; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_crtc {TYPE_1__* primary; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fb; } ;

/* Variables and functions */
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 

__attribute__((used)) static bool cdv_intel_pipe_enabled(struct drm_device *dev, int pipe)
{
	struct drm_crtc *crtc;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc = NULL;

	crtc = dev_priv->pipe_to_crtc_mapping[pipe];
	gma_crtc = to_gma_crtc(crtc);

	if (crtc->primary->fb == NULL || !gma_crtc->active)
		return false;
	return true;
}