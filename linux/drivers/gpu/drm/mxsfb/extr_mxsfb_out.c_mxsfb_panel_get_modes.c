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
 struct mxsfb_drm_private* drm_connector_to_mxsfb_drm_private (struct drm_connector*) ; 
 int drm_panel_get_modes (scalar_t__) ; 

__attribute__((used)) static int mxsfb_panel_get_modes(struct drm_connector *connector)
{
	struct mxsfb_drm_private *mxsfb =
			drm_connector_to_mxsfb_drm_private(connector);

	if (mxsfb->panel)
		return drm_panel_get_modes(mxsfb->panel);

	return 0;
}