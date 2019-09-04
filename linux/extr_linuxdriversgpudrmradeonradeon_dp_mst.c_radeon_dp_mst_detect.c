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
struct radeon_connector {int /*<<< orphan*/  port; int /*<<< orphan*/  mst_mgr; struct radeon_connector* mst_port; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int drm_dp_mst_detect_port (struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
radeon_dp_mst_detect(struct drm_connector *connector, bool force)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector *master = radeon_connector->mst_port;

	return drm_dp_mst_detect_port(connector, &master->mst_mgr, radeon_connector->port);
}