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
struct TYPE_10__ {TYPE_1__* dev_ops; } ;
struct intel_dvo {TYPE_5__ dev; } ;
struct drm_display_mode {int clock; int flags; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_9__ {int max_dotclk_freq; } ;
struct TYPE_7__ {struct drm_display_mode* fixed_mode; } ;
struct TYPE_8__ {TYPE_2__ panel; } ;
struct TYPE_6__ {int (* mode_valid ) (TYPE_5__*,struct drm_display_mode*) ;} ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_PANEL ; 
 struct intel_dvo* intel_attached_dvo (struct drm_connector*) ; 
 int stub1 (TYPE_5__*,struct drm_display_mode*) ; 
 TYPE_4__* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_mode_status
intel_dvo_mode_valid(struct drm_connector *connector,
		     struct drm_display_mode *mode)
{
	struct intel_dvo *intel_dvo = intel_attached_dvo(connector);
	const struct drm_display_mode *fixed_mode =
		to_intel_connector(connector)->panel.fixed_mode;
	int max_dotclk = to_i915(connector->dev)->max_dotclk_freq;
	int target_clock = mode->clock;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	/* XXX: Validate clock range */

	if (fixed_mode) {
		if (mode->hdisplay > fixed_mode->hdisplay)
			return MODE_PANEL;
		if (mode->vdisplay > fixed_mode->vdisplay)
			return MODE_PANEL;

		target_clock = fixed_mode->clock;
	}

	if (target_clock > max_dotclk)
		return MODE_CLOCK_HIGH;

	return intel_dvo->dev.dev_ops->mode_valid(&intel_dvo->dev, mode);
}