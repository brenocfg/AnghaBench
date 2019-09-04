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
struct drm_connector {TYPE_2__* dev; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  content_type_property; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONTENT_TYPE_NO_DATA ; 
 int /*<<< orphan*/  drm_mode_create_content_type_property (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_connector_attach_content_type_property(struct drm_connector *connector)
{
	if (!drm_mode_create_content_type_property(connector->dev))
		drm_object_attach_property(&connector->base,
					   connector->dev->mode_config.content_type_property,
					   DRM_MODE_CONTENT_TYPE_NO_DATA);
	return 0;
}