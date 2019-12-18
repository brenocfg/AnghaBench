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
struct TYPE_3__ {scalar_t__ max_tmds_clock; int /*<<< orphan*/  type; } ;
struct intel_hdmi {int has_hdmi_sink; int has_audio; TYPE_1__ dp_dual_mode; } ;
struct drm_connector {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * detect_edid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DP_DUAL_MODE_NONE ; 
 struct intel_hdmi* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static void
intel_hdmi_unset_edid(struct drm_connector *connector)
{
	struct intel_hdmi *intel_hdmi = intel_attached_hdmi(connector);

	intel_hdmi->has_hdmi_sink = false;
	intel_hdmi->has_audio = false;

	intel_hdmi->dp_dual_mode.type = DRM_DP_DUAL_MODE_NONE;
	intel_hdmi->dp_dual_mode.max_tmds_clock = 0;

	kfree(to_intel_connector(connector)->detect_edid);
	to_intel_connector(connector)->detect_edid = NULL;
}