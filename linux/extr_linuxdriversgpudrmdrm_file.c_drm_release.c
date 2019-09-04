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
struct inode {int dummy; } ;
struct file {struct drm_file* private_data; } ;
struct drm_minor {struct drm_device* dev; } ;
struct drm_file {int /*<<< orphan*/  lhead; struct drm_minor* minor; } ;
struct drm_device {int /*<<< orphan*/  open_count; int /*<<< orphan*/  filelist_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dev_is_unplugged (struct drm_device*) ; 
 int /*<<< orphan*/  drm_file_free (struct drm_file*) ; 
 int /*<<< orphan*/  drm_global_mutex ; 
 int /*<<< orphan*/  drm_lastclose (struct drm_device*) ; 
 int /*<<< orphan*/  drm_minor_release (struct drm_minor*) ; 
 int /*<<< orphan*/  drm_put_dev (struct drm_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_release(struct inode *inode, struct file *filp)
{
	struct drm_file *file_priv = filp->private_data;
	struct drm_minor *minor = file_priv->minor;
	struct drm_device *dev = minor->dev;

	mutex_lock(&drm_global_mutex);

	DRM_DEBUG("open_count = %d\n", dev->open_count);

	mutex_lock(&dev->filelist_mutex);
	list_del(&file_priv->lhead);
	mutex_unlock(&dev->filelist_mutex);

	drm_file_free(file_priv);

	if (!--dev->open_count) {
		drm_lastclose(dev);
		if (drm_dev_is_unplugged(dev))
			drm_put_dev(dev);
	}
	mutex_unlock(&drm_global_mutex);

	drm_minor_release(minor);

	return 0;
}