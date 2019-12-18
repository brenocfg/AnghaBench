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
struct intel_dp {int /*<<< orphan*/  mst_mgr; } ;
struct intel_connector {int /*<<< orphan*/  port; struct intel_dp* mst_port; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_disconnected ; 
 scalar_t__ drm_connector_is_unregistered (struct drm_connector*) ; 
 int drm_dp_mst_detect_port (struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
intel_dp_mst_detect(struct drm_connector *connector, bool force)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct intel_dp *intel_dp = intel_connector->mst_port;

	if (drm_connector_is_unregistered(connector))
		return connector_status_disconnected;
	return drm_dp_mst_detect_port(connector, &intel_dp->mst_mgr,
				      intel_connector->port);
}