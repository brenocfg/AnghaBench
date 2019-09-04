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
struct xen_drm_front_drm_pipeline {int conn_connected; } ;
struct xen_drm_front_drm_info {int /*<<< orphan*/  drm_dev; } ;
struct drm_connector {int polled; } ;

/* Variables and functions */
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  connector_funcs ; 
 int /*<<< orphan*/  connector_helper_funcs ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xen_drm_front_drm_pipeline* to_xen_drm_pipeline (struct drm_connector*) ; 

int xen_drm_front_conn_init(struct xen_drm_front_drm_info *drm_info,
			    struct drm_connector *connector)
{
	struct xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(connector);

	drm_connector_helper_add(connector, &connector_helper_funcs);

	pipeline->conn_connected = true;

	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;

	return drm_connector_init(drm_info->drm_dev, connector,
				  &connector_funcs, DRM_MODE_CONNECTOR_VIRTUAL);
}