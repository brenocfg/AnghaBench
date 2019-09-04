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
struct drm_prime_handle {int /*<<< orphan*/  handle; int /*<<< orphan*/  fd; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* prime_fd_to_handle ) (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_PRIME ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int drm_prime_fd_to_handle_ioctl(struct drm_device *dev, void *data,
				 struct drm_file *file_priv)
{
	struct drm_prime_handle *args = data;

	if (!drm_core_check_feature(dev, DRIVER_PRIME))
		return -EINVAL;

	if (!dev->driver->prime_fd_to_handle)
		return -ENOSYS;

	return dev->driver->prime_fd_to_handle(dev, file_priv,
			args->fd, &args->handle);
}