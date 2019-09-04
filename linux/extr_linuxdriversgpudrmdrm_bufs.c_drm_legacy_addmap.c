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
struct drm_map_list {struct drm_local_map* map; } ;
struct drm_local_map {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  enum drm_map_type { ____Placeholder_drm_map_type } drm_map_type ;
typedef  enum drm_map_flags { ____Placeholder_drm_map_flags } drm_map_flags ;

/* Variables and functions */
 int drm_addmap_core (struct drm_device*,int /*<<< orphan*/ ,unsigned int,int,int,struct drm_map_list**) ; 

int drm_legacy_addmap(struct drm_device *dev, resource_size_t offset,
		      unsigned int size, enum drm_map_type type,
		      enum drm_map_flags flags, struct drm_local_map **map_ptr)
{
	struct drm_map_list *list;
	int rc;

	rc = drm_addmap_core(dev, offset, size, type, flags, &list);
	if (!rc)
		*map_ptr = list->map;
	return rc;
}