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
struct vmw_fpriv {int /*<<< orphan*/  tfile; scalar_t__ locked_master; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  drm_master_put (scalar_t__*) ; 
 int /*<<< orphan*/  kfree (struct vmw_fpriv*) ; 
 int /*<<< orphan*/  ttm_lock_set_kill (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_object_file_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_vt_unlock (int /*<<< orphan*/ *) ; 
 struct vmw_fpriv* vmw_fpriv (struct drm_file*) ; 
 struct vmw_master* vmw_master (scalar_t__) ; 

__attribute__((used)) static void vmw_postclose(struct drm_device *dev,
			 struct drm_file *file_priv)
{
	struct vmw_fpriv *vmw_fp;

	vmw_fp = vmw_fpriv(file_priv);

	if (vmw_fp->locked_master) {
		struct vmw_master *vmaster =
			vmw_master(vmw_fp->locked_master);

		ttm_lock_set_kill(&vmaster->lock, true, SIGTERM);
		ttm_vt_unlock(&vmaster->lock);
		drm_master_put(&vmw_fp->locked_master);
	}

	ttm_object_file_release(&vmw_fp->tfile);
	kfree(vmw_fp);
}