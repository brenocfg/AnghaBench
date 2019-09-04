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
struct intel_connector {struct drm_connector* edid; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static void
intel_dp_mst_connector_destroy(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);

	if (!IS_ERR_OR_NULL(intel_connector->edid))
		kfree(intel_connector->edid);

	drm_connector_cleanup(connector);
	kfree(connector);
}