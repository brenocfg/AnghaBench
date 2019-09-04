#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_connector {int dummy; } ;
struct TYPE_4__ {scalar_t__ cec_notifier; } ;
struct TYPE_3__ {struct drm_connector* detect_edid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_put (scalar_t__) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 TYPE_2__* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 TYPE_1__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static void intel_hdmi_destroy(struct drm_connector *connector)
{
	if (intel_attached_hdmi(connector)->cec_notifier)
		cec_notifier_put(intel_attached_hdmi(connector)->cec_notifier);
	kfree(to_intel_connector(connector)->detect_edid);
	drm_connector_cleanup(connector);
	kfree(connector);
}