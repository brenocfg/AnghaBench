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
struct drm_syncobj_handle {int flags; int /*<<< orphan*/  handle; int /*<<< orphan*/  fd; scalar_t__ pad; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_SYNCOBJ ; 
 int DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_FILE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_syncobj_fd_to_handle (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_syncobj_import_sync_file_fence (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
drm_syncobj_fd_to_handle_ioctl(struct drm_device *dev, void *data,
				   struct drm_file *file_private)
{
	struct drm_syncobj_handle *args = data;

	if (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		return -EOPNOTSUPP;

	if (args->pad)
		return -EINVAL;

	if (args->flags != 0 &&
	    args->flags != DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_FILE)
		return -EINVAL;

	if (args->flags & DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_FILE)
		return drm_syncobj_import_sync_file_fence(file_private,
							  args->fd,
							  args->handle);

	return drm_syncobj_fd_to_handle(file_private, args->fd,
					&args->handle);
}