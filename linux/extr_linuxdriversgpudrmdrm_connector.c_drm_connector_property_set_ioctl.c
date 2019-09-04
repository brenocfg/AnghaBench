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
struct drm_mode_obj_set_property {int /*<<< orphan*/  obj_type; int /*<<< orphan*/  obj_id; int /*<<< orphan*/  prop_id; int /*<<< orphan*/  value; } ;
struct drm_mode_connector_set_property {int /*<<< orphan*/  connector_id; int /*<<< orphan*/  prop_id; int /*<<< orphan*/  value; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_CONNECTOR ; 
 int drm_mode_obj_set_property_ioctl (struct drm_device*,struct drm_mode_obj_set_property*,struct drm_file*) ; 

int drm_connector_property_set_ioctl(struct drm_device *dev,
				     void *data, struct drm_file *file_priv)
{
	struct drm_mode_connector_set_property *conn_set_prop = data;
	struct drm_mode_obj_set_property obj_set_prop = {
		.value = conn_set_prop->value,
		.prop_id = conn_set_prop->prop_id,
		.obj_id = conn_set_prop->connector_id,
		.obj_type = DRM_MODE_OBJECT_CONNECTOR
	};

	/* It does all the locking and checking we need */
	return drm_mode_obj_set_property_ioctl(dev, &obj_set_prop, file_priv);
}