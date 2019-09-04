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
struct intel_hdmi {int dummy; } ;
struct drm_connector {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  picture_aspect_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_NONE ; 
 int /*<<< orphan*/  drm_connector_attach_content_type_property (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_attach_aspect_ratio_property (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_attach_broadcast_rgb_property (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_attach_force_audio_property (struct drm_connector*) ; 

__attribute__((used)) static void
intel_hdmi_add_properties(struct intel_hdmi *intel_hdmi, struct drm_connector *connector)
{
	intel_attach_force_audio_property(connector);
	intel_attach_broadcast_rgb_property(connector);
	intel_attach_aspect_ratio_property(connector);
	drm_connector_attach_content_type_property(connector);
	connector->state->picture_aspect_ratio = HDMI_PICTURE_ASPECT_NONE;
}