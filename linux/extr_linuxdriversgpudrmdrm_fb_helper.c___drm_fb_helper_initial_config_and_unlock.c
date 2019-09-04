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
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {scalar_t__ pixclock; } ;
struct fb_info {TYPE_3__ fix; int /*<<< orphan*/  node; TYPE_2__ var; } ;
struct drm_fb_helper {int preferred_bpp; int deferred_setup; int /*<<< orphan*/  kernel_fb_list; int /*<<< orphan*/  lock; struct fb_info* fbdev; struct drm_device* dev; } ;
struct TYPE_4__ {unsigned int max_width; unsigned int max_height; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_single_fb_probe (struct drm_fb_helper*,int) ; 
 int /*<<< orphan*/  drm_setup_crtcs (struct drm_fb_helper*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  drm_setup_crtcs_fb (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  kernel_fb_helper_list ; 
 int /*<<< orphan*/  kernel_fb_helper_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  register_sysrq_key (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysrq_drm_fb_helper_restore_op ; 

__attribute__((used)) static int
__drm_fb_helper_initial_config_and_unlock(struct drm_fb_helper *fb_helper,
					  int bpp_sel)
{
	struct drm_device *dev = fb_helper->dev;
	struct fb_info *info;
	unsigned int width, height;
	int ret;

	width = dev->mode_config.max_width;
	height = dev->mode_config.max_height;

	drm_setup_crtcs(fb_helper, width, height);
	ret = drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
	if (ret < 0) {
		if (ret == -EAGAIN) {
			fb_helper->preferred_bpp = bpp_sel;
			fb_helper->deferred_setup = true;
			ret = 0;
		}
		mutex_unlock(&fb_helper->lock);

		return ret;
	}
	drm_setup_crtcs_fb(fb_helper);

	fb_helper->deferred_setup = false;

	info = fb_helper->fbdev;
	info->var.pixclock = 0;

	/* Need to drop locks to avoid recursive deadlock in
	 * register_framebuffer. This is ok because the only thing left to do is
	 * register the fbdev emulation instance in kernel_fb_helper_list. */
	mutex_unlock(&fb_helper->lock);

	ret = register_framebuffer(info);
	if (ret < 0)
		return ret;

	dev_info(dev->dev, "fb%d: %s frame buffer device\n",
		 info->node, info->fix.id);

	mutex_lock(&kernel_fb_helper_lock);
	if (list_empty(&kernel_fb_helper_list))
		register_sysrq_key('v', &sysrq_drm_fb_helper_restore_op);

	list_add(&fb_helper->kernel_fb_list, &kernel_fb_helper_list);
	mutex_unlock(&kernel_fb_helper_lock);

	return 0;
}