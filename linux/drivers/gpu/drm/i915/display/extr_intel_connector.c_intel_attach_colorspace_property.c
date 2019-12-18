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
struct drm_connector {int /*<<< orphan*/  colorspace_property; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_create_colorspace_property (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
intel_attach_colorspace_property(struct drm_connector *connector)
{
	if (!drm_mode_create_colorspace_property(connector))
		drm_object_attach_property(&connector->base,
					   connector->colorspace_property, 0);
}