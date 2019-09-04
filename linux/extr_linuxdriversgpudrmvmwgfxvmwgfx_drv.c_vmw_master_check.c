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
struct vmw_master {int /*<<< orphan*/  lock; } ;
struct vmw_fpriv {scalar_t__ locked_master; } ;
struct drm_file {int /*<<< orphan*/  master; } ;
struct drm_device {int /*<<< orphan*/  master_mutex; } ;

/* Variables and functions */
 unsigned int DRM_AUTH ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 unsigned int DRM_RENDER_ALLOW ; 
 int EACCES ; 
 int ERESTARTSYS ; 
 struct vmw_master* ERR_PTR (int) ; 
 scalar_t__ drm_is_current_master (struct drm_file*) ; 
 int /*<<< orphan*/  drm_is_primary_client (struct drm_file*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 struct vmw_fpriv* vmw_fpriv (struct drm_file*) ; 
 struct vmw_master* vmw_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vmw_master *vmw_master_check(struct drm_device *dev,
					   struct drm_file *file_priv,
					   unsigned int flags)
{
	int ret;
	struct vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);
	struct vmw_master *vmaster;

	if (!drm_is_primary_client(file_priv) || !(flags & DRM_AUTH))
		return NULL;

	ret = mutex_lock_interruptible(&dev->master_mutex);
	if (unlikely(ret != 0))
		return ERR_PTR(-ERESTARTSYS);

	if (drm_is_current_master(file_priv)) {
		mutex_unlock(&dev->master_mutex);
		return NULL;
	}

	/*
	 * Check if we were previously master, but now dropped. In that
	 * case, allow at least render node functionality.
	 */
	if (vmw_fp->locked_master) {
		mutex_unlock(&dev->master_mutex);

		if (flags & DRM_RENDER_ALLOW)
			return NULL;

		DRM_ERROR("Dropped master trying to access ioctl that "
			  "requires authentication.\n");
		return ERR_PTR(-EACCES);
	}
	mutex_unlock(&dev->master_mutex);

	/*
	 * Take the TTM lock. Possibly sleep waiting for the authenticating
	 * master to become master again, or for a SIGTERM if the
	 * authenticating master exits.
	 */
	vmaster = vmw_master(file_priv->master);
	ret = ttm_read_lock(&vmaster->lock, true);
	if (unlikely(ret != 0))
		vmaster = ERR_PTR(ret);

	return vmaster;
}