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
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct mxsfb_drm_private* drm_connector_to_mxsfb_drm_private (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
mxsfb_panel_connector_detect(struct drm_connector *connector, bool force)
{
	struct mxsfb_drm_private *mxsfb =
			drm_connector_to_mxsfb_drm_private(connector);

	if (mxsfb->panel)
		return connector_status_connected;

	return connector_status_disconnected;
}