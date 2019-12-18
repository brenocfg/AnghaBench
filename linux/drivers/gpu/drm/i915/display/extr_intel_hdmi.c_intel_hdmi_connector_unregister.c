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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_remove_i2c_symlink (struct drm_connector*) ; 

__attribute__((used)) static void intel_hdmi_connector_unregister(struct drm_connector *connector)
{
	intel_hdmi_remove_i2c_symlink(connector);

	intel_connector_unregister(connector);
}