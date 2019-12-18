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
struct drm_file {struct drm_minor* minor; } ;
struct drm_device {int /*<<< orphan*/  open_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_close_helper (struct file*) ; 
 int /*<<< orphan*/  drm_global_mutex ; 
 int /*<<< orphan*/  drm_lastclose (struct drm_device*) ; 
 int /*<<< orphan*/  drm_minor_release (struct drm_minor*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_release(struct inode *inode, struct file *filp)
{
	struct drm_file *file_priv = filp->private_data;
	struct drm_minor *minor = file_priv->minor;
	struct drm_device *dev = minor->dev;

	mutex_lock(&drm_global_mutex);

	DRM_DEBUG("open_count = %d\n", dev->open_count);

	drm_close_helper(filp);

	if (!--dev->open_count)
		drm_lastclose(dev);

	mutex_unlock(&drm_global_mutex);

	drm_minor_release(minor);

	return 0;
}