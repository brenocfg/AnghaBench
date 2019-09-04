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
struct intel_dp {int /*<<< orphan*/  aux; int /*<<< orphan*/  has_audio; struct intel_connector* attached_connector; } ;
struct intel_connector {struct edid* detect_edid; } ;
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_detect_monitor_audio (struct edid*) ; 
 int /*<<< orphan*/  drm_dp_cec_set_edid (int /*<<< orphan*/ *,struct edid*) ; 
 struct edid* intel_dp_get_edid (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_unset_edid (struct intel_dp*) ; 

__attribute__((used)) static void
intel_dp_set_edid(struct intel_dp *intel_dp)
{
	struct intel_connector *intel_connector = intel_dp->attached_connector;
	struct edid *edid;

	intel_dp_unset_edid(intel_dp);
	edid = intel_dp_get_edid(intel_dp);
	intel_connector->detect_edid = edid;

	intel_dp->has_audio = drm_detect_monitor_audio(edid);
	drm_dp_cec_set_edid(&intel_dp->aux, edid);
}