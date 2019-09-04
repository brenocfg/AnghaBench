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
struct drm_local_map {scalar_t__ type; int /*<<< orphan*/  handle; int /*<<< orphan*/  size; } ;
struct drm_device {TYPE_1__* agp; } ;
struct TYPE_2__ {scalar_t__ cant_use_aperture; } ;

/* Variables and functions */
 scalar_t__ _DRM_AGP ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

void drm_legacy_ioremapfree(struct drm_local_map *map, struct drm_device *dev)
{
	if (!map->handle || !map->size)
		return;

	if (dev->agp && dev->agp->cant_use_aperture && map->type == _DRM_AGP)
		vunmap(map->handle);
	else
		iounmap(map->handle);
}