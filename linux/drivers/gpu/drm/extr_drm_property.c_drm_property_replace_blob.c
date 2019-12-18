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
struct drm_property_blob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_property_blob_get (struct drm_property_blob*) ; 
 int /*<<< orphan*/  drm_property_blob_put (struct drm_property_blob*) ; 

bool drm_property_replace_blob(struct drm_property_blob **blob,
			       struct drm_property_blob *new_blob)
{
	struct drm_property_blob *old_blob = *blob;

	if (old_blob == new_blob)
		return false;

	drm_property_blob_put(old_blob);
	if (new_blob)
		drm_property_blob_get(new_blob);
	*blob = new_blob;
	return true;
}