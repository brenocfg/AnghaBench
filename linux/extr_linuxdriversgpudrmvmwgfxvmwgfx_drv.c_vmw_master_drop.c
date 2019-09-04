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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct vmw_private {TYPE_1__ fbdev_master; TYPE_1__* active_master; int /*<<< orphan*/  enable_fb; } ;
struct vmw_master {int /*<<< orphan*/  lock; } ;
struct vmw_fpriv {int /*<<< orphan*/  locked_master; int /*<<< orphan*/  tfile; } ;
struct drm_file {int /*<<< orphan*/  master; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  drm_master_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_master_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_lock_set_kill (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ttm_vt_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_vt_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct vmw_fpriv* vmw_fpriv (struct drm_file*) ; 
 int /*<<< orphan*/  vmw_kms_legacy_hotspot_clear (struct vmw_private*) ; 
 struct vmw_master* vmw_master (int /*<<< orphan*/ ) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_svga_disable (struct vmw_private*) ; 

__attribute__((used)) static void vmw_master_drop(struct drm_device *dev,
			    struct drm_file *file_priv)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);
	struct vmw_master *vmaster = vmw_master(file_priv->master);
	int ret;

	/**
	 * Make sure the master doesn't disappear while we have
	 * it locked.
	 */

	vmw_fp->locked_master = drm_master_get(file_priv->master);
	ret = ttm_vt_lock(&vmaster->lock, false, vmw_fp->tfile);
	vmw_kms_legacy_hotspot_clear(dev_priv);
	if (unlikely((ret != 0))) {
		DRM_ERROR("Unable to lock TTM at VT switch.\n");
		drm_master_put(&vmw_fp->locked_master);
	}

	ttm_lock_set_kill(&vmaster->lock, false, SIGTERM);

	if (!dev_priv->enable_fb)
		vmw_svga_disable(dev_priv);

	dev_priv->active_master = &dev_priv->fbdev_master;
	ttm_lock_set_kill(&dev_priv->fbdev_master.lock, false, SIGTERM);
	ttm_vt_unlock(&dev_priv->fbdev_master.lock);
}