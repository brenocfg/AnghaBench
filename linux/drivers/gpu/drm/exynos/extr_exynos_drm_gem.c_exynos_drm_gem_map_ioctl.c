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
struct drm_file {int dummy; } ;
struct drm_exynos_gem_map {int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_gem_dumb_map_offset (struct drm_file*,struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int exynos_drm_gem_map_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *file_priv)
{
	struct drm_exynos_gem_map *args = data;

	return drm_gem_dumb_map_offset(file_priv, dev, args->handle,
				       &args->offset);
}