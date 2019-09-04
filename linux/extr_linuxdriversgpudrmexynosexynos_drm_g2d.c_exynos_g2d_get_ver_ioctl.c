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
struct drm_exynos_g2d_get_ver {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G2D_HW_MAJOR_VER ; 
 int /*<<< orphan*/  G2D_HW_MINOR_VER ; 

int exynos_g2d_get_ver_ioctl(struct drm_device *drm_dev, void *data,
			     struct drm_file *file)
{
	struct drm_exynos_g2d_get_ver *ver = data;

	ver->major = G2D_HW_MAJOR_VER;
	ver->minor = G2D_HW_MINOR_VER;

	return 0;
}