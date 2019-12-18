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
struct drm_mode_config {int /*<<< orphan*/  edid_property; } ;
struct drm_connector {int /*<<< orphan*/  base; TYPE_1__* dev; } ;
struct TYPE_2__ {struct drm_mode_config mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drm_connector_attach_edid_property(struct drm_connector *connector)
{
	struct drm_mode_config *config = &connector->dev->mode_config;

	drm_object_attach_property(&connector->base,
				   config->edid_property,
				   0);
}