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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_property_blob {TYPE_1__ base; } ;
struct drm_property {int dummy; } ;
struct drm_mode_object {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_property_blob*) ; 
 int PTR_ERR (struct drm_property_blob*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int drm_object_property_set_value (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_blob_put (struct drm_property_blob*) ; 
 struct drm_property_blob* drm_property_create_blob (struct drm_device*,size_t,void const*) ; 

int drm_property_replace_global_blob(struct drm_device *dev,
				     struct drm_property_blob **replace,
				     size_t length,
				     const void *data,
				     struct drm_mode_object *obj_holds_id,
				     struct drm_property *prop_holds_id)
{
	struct drm_property_blob *new_blob = NULL;
	struct drm_property_blob *old_blob = NULL;
	int ret;

	WARN_ON(replace == NULL);

	old_blob = *replace;

	if (length && data) {
		new_blob = drm_property_create_blob(dev, length, data);
		if (IS_ERR(new_blob))
			return PTR_ERR(new_blob);
	}

	if (obj_holds_id) {
		ret = drm_object_property_set_value(obj_holds_id,
						    prop_holds_id,
						    new_blob ?
						        new_blob->base.id : 0);
		if (ret != 0)
			goto err_created;
	}

	drm_property_blob_put(old_blob);
	*replace = new_blob;

	return 0;

err_created:
	drm_property_blob_put(new_blob);
	return ret;
}