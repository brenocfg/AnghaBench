#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {struct drm_file* private_data; } ;
struct drm_ioctl_desc {unsigned int cmd; unsigned int flags; } ;
struct drm_file {TYPE_1__* minor; } ;
struct drm_device {TYPE_2__* driver; } ;
struct TYPE_4__ {unsigned int num_ioctls; } ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 unsigned int DRM_COMMAND_BASE ; 
 unsigned int DRM_COMMAND_END ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 unsigned int DRM_IOCTL_NR (unsigned int) ; 
 unsigned int DRM_VMW_EXECBUF ; 
 unsigned int DRM_VMW_UPDATE_LAYOUT ; 
 long EACCES ; 
 long EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_ioctl_flags (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  drm_is_current_master (struct drm_file*) ; 
 scalar_t__ unlikely (int) ; 
 struct drm_ioctl_desc* vmw_ioctls ; 

__attribute__((used)) static long vmw_generic_ioctl(struct file *filp, unsigned int cmd,
			      unsigned long arg,
			      long (*ioctl_func)(struct file *, unsigned int,
						 unsigned long))
{
	struct drm_file *file_priv = filp->private_data;
	struct drm_device *dev = file_priv->minor->dev;
	unsigned int nr = DRM_IOCTL_NR(cmd);
	unsigned int flags;

	/*
	 * Do extra checking on driver private ioctls.
	 */

	if ((nr >= DRM_COMMAND_BASE) && (nr < DRM_COMMAND_END)
	    && (nr < DRM_COMMAND_BASE + dev->driver->num_ioctls)) {
		const struct drm_ioctl_desc *ioctl =
			&vmw_ioctls[nr - DRM_COMMAND_BASE];

		if (nr == DRM_COMMAND_BASE + DRM_VMW_EXECBUF) {
			return ioctl_func(filp, cmd, arg);
		} else if (nr == DRM_COMMAND_BASE + DRM_VMW_UPDATE_LAYOUT) {
			if (!drm_is_current_master(file_priv) &&
			    !capable(CAP_SYS_ADMIN))
				return -EACCES;
		}

		if (unlikely(ioctl->cmd != cmd))
			goto out_io_encoding;

		flags = ioctl->flags;
	} else if (!drm_ioctl_flags(nr, &flags))
		return -EINVAL;

	return ioctl_func(filp, cmd, arg);

out_io_encoding:
	DRM_ERROR("Invalid command format, ioctl %d\n",
		  nr - DRM_COMMAND_BASE);

	return -EINVAL;
}