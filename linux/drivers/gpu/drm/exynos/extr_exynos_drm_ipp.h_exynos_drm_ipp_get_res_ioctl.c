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
struct drm_exynos_ioctl_ipp_get_res {scalar_t__ count_ipps; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int exynos_drm_ipp_get_res_ioctl(struct drm_device *dev,
	 void *data, struct drm_file *file_priv)
{
	struct drm_exynos_ioctl_ipp_get_res *resp = data;

	resp->count_ipps = 0;
	return 0;
}