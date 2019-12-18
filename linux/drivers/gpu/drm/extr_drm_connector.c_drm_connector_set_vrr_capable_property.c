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
struct drm_connector {int /*<<< orphan*/  vrr_capable_property; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_object_property_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void drm_connector_set_vrr_capable_property(
		struct drm_connector *connector, bool capable)
{
	drm_object_property_set_value(&connector->base,
				      connector->vrr_capable_property,
				      capable);
}