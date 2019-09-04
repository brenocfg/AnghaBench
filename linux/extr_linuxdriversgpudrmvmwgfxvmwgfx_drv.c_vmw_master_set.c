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
struct vmw_private {struct vmw_master* active_master; struct vmw_master fbdev_master; } ;
struct vmw_fpriv {scalar_t__ locked_master; int /*<<< orphan*/  tfile; } ;
struct drm_file {scalar_t__ master; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  drm_master_put (scalar_t__*) ; 
 int /*<<< orphan*/  drm_sysfs_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  ttm_lock_set_kill (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ttm_vt_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_vt_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct vmw_fpriv* vmw_fpriv (struct drm_file*) ; 
 struct vmw_master* vmw_master (scalar_t__) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

__attribute__((used)) static int vmw_master_set(struct drm_device *dev,
			  struct drm_file *file_priv,
			  bool from_open)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);
	struct vmw_master *active = dev_priv->active_master;
	struct vmw_master *vmaster = vmw_master(file_priv->master);
	int ret = 0;

	if (active) {
		BUG_ON(active != &dev_priv->fbdev_master);
		ret = ttm_vt_lock(&active->lock, false, vmw_fp->tfile);
		if (unlikely(ret != 0))
			return ret;

		ttm_lock_set_kill(&active->lock, true, SIGTERM);
		dev_priv->active_master = NULL;
	}

	ttm_lock_set_kill(&vmaster->lock, false, SIGTERM);
	if (!from_open) {
		ttm_vt_unlock(&vmaster->lock);
		BUG_ON(vmw_fp->locked_master != file_priv->master);
		drm_master_put(&vmw_fp->locked_master);
	}

	dev_priv->active_master = vmaster;
	drm_sysfs_hotplug_event(dev);

	return 0;
}