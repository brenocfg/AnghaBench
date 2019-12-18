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
struct vmw_private {struct fb_info* fb_info; } ;
struct vmw_fb_par {int /*<<< orphan*/  vmalloc; int /*<<< orphan*/  bo_mutex; int /*<<< orphan*/  local_work; } ;
struct fb_info {struct vmw_fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fb_kms_detach (struct vmw_fb_par*,int,int) ; 

int vmw_fb_close(struct vmw_private *vmw_priv)
{
	struct fb_info *info;
	struct vmw_fb_par *par;

	if (!vmw_priv->fb_info)
		return 0;

	info = vmw_priv->fb_info;
	par = info->par;

	/* ??? order */
	fb_deferred_io_cleanup(info);
	cancel_delayed_work_sync(&par->local_work);
	unregister_framebuffer(info);

	mutex_lock(&par->bo_mutex);
	(void) vmw_fb_kms_detach(par, true, true);
	mutex_unlock(&par->bo_mutex);

	vfree(par->vmalloc);
	framebuffer_release(info);

	return 0;
}