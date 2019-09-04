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
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {struct edid* detect_edid; } ;

/* Variables and functions */
 int intel_connector_update_modes (struct drm_connector*,struct edid*) ; 
 TYPE_1__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int intel_hdmi_get_modes(struct drm_connector *connector)
{
	struct edid *edid;

	edid = to_intel_connector(connector)->detect_edid;
	if (edid == NULL)
		return 0;

	return intel_connector_update_modes(connector, edid);
}