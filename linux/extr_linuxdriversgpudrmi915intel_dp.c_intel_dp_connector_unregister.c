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
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_aux_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_cec_unregister_connector (int /*<<< orphan*/ *) ; 
 struct intel_dp* intel_attached_dp (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_connector_unregister (struct drm_connector*) ; 

__attribute__((used)) static void
intel_dp_connector_unregister(struct drm_connector *connector)
{
	struct intel_dp *intel_dp = intel_attached_dp(connector);

	drm_dp_cec_unregister_connector(&intel_dp->aux);
	drm_dp_aux_unregister(&intel_dp->aux);
	intel_connector_unregister(connector);
}