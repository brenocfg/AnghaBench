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
struct mxsfb_drm_private {scalar_t__ panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 struct mxsfb_drm_private* drm_connector_to_mxsfb_drm_private (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 

__attribute__((used)) static void mxsfb_panel_connector_destroy(struct drm_connector *connector)
{
	struct mxsfb_drm_private *mxsfb =
			drm_connector_to_mxsfb_drm_private(connector);

	if (mxsfb->panel)
		drm_panel_detach(mxsfb->panel);

	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
}