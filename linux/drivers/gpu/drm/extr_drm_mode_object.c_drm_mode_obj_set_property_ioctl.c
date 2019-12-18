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
struct drm_property {int /*<<< orphan*/  dev; } ;
struct drm_mode_object {int /*<<< orphan*/  properties; } ;
struct drm_mode_obj_set_property {int /*<<< orphan*/  value; int /*<<< orphan*/  prop_id; int /*<<< orphan*/  obj_type; int /*<<< orphan*/  obj_id; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 struct drm_property* drm_mode_obj_find_prop_id (struct drm_mode_object*,int /*<<< orphan*/ ) ; 
 struct drm_mode_object* drm_mode_object_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_object_put (struct drm_mode_object*) ; 
 int set_property_atomic (struct drm_mode_object*,struct drm_file*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int set_property_legacy (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 

int drm_mode_obj_set_property_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv)
{
	struct drm_mode_obj_set_property *arg = data;
	struct drm_mode_object *arg_obj;
	struct drm_property *property;
	int ret = -EINVAL;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	arg_obj = drm_mode_object_find(dev, file_priv, arg->obj_id, arg->obj_type);
	if (!arg_obj)
		return -ENOENT;

	if (!arg_obj->properties)
		goto out_unref;

	property = drm_mode_obj_find_prop_id(arg_obj, arg->prop_id);
	if (!property)
		goto out_unref;

	if (drm_drv_uses_atomic_modeset(property->dev))
		ret = set_property_atomic(arg_obj, file_priv, property, arg->value);
	else
		ret = set_property_legacy(arg_obj, property, arg->value);

out_unref:
	drm_mode_object_put(arg_obj);
	return ret;
}