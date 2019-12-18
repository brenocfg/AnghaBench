#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int drm_add_edid_modes (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gm12u320_edid ; 

__attribute__((used)) static int gm12u320_conn_get_modes(struct drm_connector *connector)
{
	drm_connector_update_edid_property(connector, &gm12u320_edid);
	return drm_add_edid_modes(connector, &gm12u320_edid);
}