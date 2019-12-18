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
struct TYPE_2__ {int /*<<< orphan*/  tv_bottom_margin_property; int /*<<< orphan*/  tv_top_margin_property; int /*<<< orphan*/  tv_right_margin_property; int /*<<< orphan*/  tv_left_margin_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector {int /*<<< orphan*/  base; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drm_connector_attach_tv_margin_properties(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;

	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_left_margin_property,
				   0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_right_margin_property,
				   0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_top_margin_property,
				   0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_bottom_margin_property,
				   0);
}