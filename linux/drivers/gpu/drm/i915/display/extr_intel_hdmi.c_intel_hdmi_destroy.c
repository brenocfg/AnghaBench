#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_connector {int dummy; } ;
struct TYPE_2__ {scalar_t__ cec_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_put (scalar_t__) ; 
 TYPE_1__* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_connector_destroy (struct drm_connector*) ; 

__attribute__((used)) static void intel_hdmi_destroy(struct drm_connector *connector)
{
	if (intel_attached_hdmi(connector)->cec_notifier)
		cec_notifier_put(intel_attached_hdmi(connector)->cec_notifier);

	intel_connector_destroy(connector);
}