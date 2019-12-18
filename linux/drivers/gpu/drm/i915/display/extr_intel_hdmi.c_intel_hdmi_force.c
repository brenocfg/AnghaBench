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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {scalar_t__ status; int /*<<< orphan*/  name; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ connector_status_connected ; 
 int /*<<< orphan*/  intel_hdmi_set_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_unset_edid (struct drm_connector*) ; 

__attribute__((used)) static void
intel_hdmi_force(struct drm_connector *connector)
{
	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	intel_hdmi_unset_edid(connector);

	if (connector->status != connector_status_connected)
		return;

	intel_hdmi_set_edid(connector);
}