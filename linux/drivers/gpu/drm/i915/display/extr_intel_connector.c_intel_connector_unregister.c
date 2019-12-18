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
struct intel_connector {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_backlight_device_unregister (struct intel_connector*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

void intel_connector_unregister(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);

	intel_backlight_device_unregister(intel_connector);
}