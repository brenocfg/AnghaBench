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
struct intel_dp {int has_audio; int /*<<< orphan*/  aux; struct intel_connector* attached_connector; } ;
struct intel_connector {int /*<<< orphan*/ * detect_edid; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_cec_unset_edid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_dp_unset_edid(struct intel_dp *intel_dp)
{
	struct intel_connector *intel_connector = intel_dp->attached_connector;

	drm_dp_cec_unset_edid(&intel_dp->aux);
	kfree(intel_connector->detect_edid);
	intel_connector->detect_edid = NULL;

	intel_dp->has_audio = false;
}