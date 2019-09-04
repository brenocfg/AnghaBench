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
struct drm_property {int dummy; } ;
struct drm_mode_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PROP_BLOB ; 
 int /*<<< orphan*/  DRM_MODE_PROP_OBJECT ; 
 int /*<<< orphan*/  drm_mode_object_put (struct drm_mode_object*) ; 
 int /*<<< orphan*/  drm_property_blob_put (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_property_type_is (struct drm_property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_to_blob (struct drm_mode_object*) ; 

void drm_property_change_valid_put(struct drm_property *property,
		struct drm_mode_object *ref)
{
	if (!ref)
		return;

	if (drm_property_type_is(property, DRM_MODE_PROP_OBJECT)) {
		drm_mode_object_put(ref);
	} else if (drm_property_type_is(property, DRM_MODE_PROP_BLOB))
		drm_property_blob_put(obj_to_blob(ref));
}