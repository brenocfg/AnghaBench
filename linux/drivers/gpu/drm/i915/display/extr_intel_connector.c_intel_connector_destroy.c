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
struct intel_connector {scalar_t__ port; int /*<<< orphan*/  panel; struct drm_connector* edid; struct drm_connector* detect_edid; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_dp_mst_put_port_malloc (scalar_t__) ; 
 int /*<<< orphan*/  intel_hdcp_cleanup (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_panel_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

void intel_connector_destroy(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);

	kfree(intel_connector->detect_edid);

	intel_hdcp_cleanup(intel_connector);

	if (!IS_ERR_OR_NULL(intel_connector->edid))
		kfree(intel_connector->edid);

	intel_panel_fini(&intel_connector->panel);

	drm_connector_cleanup(connector);

	if (intel_connector->port)
		drm_dp_mst_put_port_malloc(intel_connector->port);

	kfree(connector);
}