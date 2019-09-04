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
struct drm_radeon_gem_mmap {int /*<<< orphan*/  addr_ptr; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int radeon_mode_dumb_mmap (struct drm_file*,struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int radeon_gem_mmap_ioctl(struct drm_device *dev, void *data,
			  struct drm_file *filp)
{
	struct drm_radeon_gem_mmap *args = data;

	return radeon_mode_dumb_mmap(filp, dev, args->handle, &args->addr_ptr);
}