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
struct drm_display_mode {int dummy; } ;
struct drm_connector_helper_funcs {int (* mode_valid ) (struct drm_connector*,struct drm_display_mode*) ;} ;
struct drm_connector {struct drm_connector_helper_funcs* helper_private; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_OK ; 
 int stub1 (struct drm_connector*,struct drm_display_mode*) ; 

enum drm_mode_status drm_connector_mode_valid(struct drm_connector *connector,
					      struct drm_display_mode *mode)
{
	const struct drm_connector_helper_funcs *connector_funcs =
		connector->helper_private;

	if (!connector_funcs || !connector_funcs->mode_valid)
		return MODE_OK;

	return connector_funcs->mode_valid(connector, mode);
}