#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; } ;
struct fb_info {TYPE_2__ cmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  funcs; } ;
struct drm_fb_helper {TYPE_3__ client; int /*<<< orphan*/  lock; int /*<<< orphan*/  kernel_fb_list; struct fb_info* fbdev; int /*<<< orphan*/  dirty_work; int /*<<< orphan*/  resume_work; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fb_helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_client_release (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_fbdev_emulation ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  kernel_fb_helper_list ; 
 int /*<<< orphan*/  kernel_fb_helper_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysrq_drm_fb_helper_restore_op ; 
 int /*<<< orphan*/  unregister_sysrq_key (char,int /*<<< orphan*/ *) ; 

void drm_fb_helper_fini(struct drm_fb_helper *fb_helper)
{
	struct fb_info *info;

	if (!fb_helper)
		return;

	fb_helper->dev->fb_helper = NULL;

	if (!drm_fbdev_emulation)
		return;

	cancel_work_sync(&fb_helper->resume_work);
	cancel_work_sync(&fb_helper->dirty_work);

	info = fb_helper->fbdev;
	if (info) {
		if (info->cmap.len)
			fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	}
	fb_helper->fbdev = NULL;

	mutex_lock(&kernel_fb_helper_lock);
	if (!list_empty(&fb_helper->kernel_fb_list)) {
		list_del(&fb_helper->kernel_fb_list);
		if (list_empty(&kernel_fb_helper_list))
			unregister_sysrq_key('v', &sysrq_drm_fb_helper_restore_op);
	}
	mutex_unlock(&kernel_fb_helper_lock);

	mutex_destroy(&fb_helper->lock);

	if (!fb_helper->client.funcs)
		drm_client_release(&fb_helper->client);
}