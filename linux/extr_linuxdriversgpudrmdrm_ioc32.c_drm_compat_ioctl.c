#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {struct drm_file* private_data; } ;
struct drm_file {int /*<<< orphan*/  authenticated; TYPE_2__* minor; } ;
typedef  int (* drm_ioctl_compat_t ) (struct file*,unsigned int,unsigned long) ;
struct TYPE_7__ {int (* fn ) (struct file*,unsigned int,unsigned long) ;int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__* kdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,...) ; 
 unsigned int DRM_IOCTL_NR (unsigned int) ; 
 int /*<<< orphan*/  current ; 
 TYPE_3__* drm_compat_ioctls ; 
 long drm_ioctl (struct file*,unsigned int,unsigned long) ; 
 scalar_t__ old_encode_dev (int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

long drm_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned int nr = DRM_IOCTL_NR(cmd);
	struct drm_file *file_priv = filp->private_data;
	drm_ioctl_compat_t *fn;
	int ret;

	/* Assume that ioctls without an explicit compat routine will just
	 * work.  This may not always be a good assumption, but it's better
	 * than always failing.
	 */
	if (nr >= ARRAY_SIZE(drm_compat_ioctls))
		return drm_ioctl(filp, cmd, arg);

	fn = drm_compat_ioctls[nr].fn;
	if (!fn)
		return drm_ioctl(filp, cmd, arg);

	DRM_DEBUG("pid=%d, dev=0x%lx, auth=%d, %s\n",
		  task_pid_nr(current),
		  (long)old_encode_dev(file_priv->minor->kdev->devt),
		  file_priv->authenticated,
		  drm_compat_ioctls[nr].name);
	ret = (*fn)(filp, cmd, arg);
	if (ret)
		DRM_DEBUG("ret = %d\n", ret);
	return ret;
}