#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  activate; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  device; TYPE_1__ var; int /*<<< orphan*/  screen_base; struct cirrusfb_info* par; } ;
struct cirrusfb_info {scalar_t__ btype; } ;

/* Variables and functions */
 scalar_t__ BT_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  assert (int) ; 
 int cirrusfb_check_var (TYPE_1__*,struct fb_info*) ; 
 int /*<<< orphan*/  cirrusfb_set_fbinfo (struct fb_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int fb_find_mode (TYPE_1__*,struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mode_option ; 
 int register_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int cirrusfb_register(struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;
	int err;

	/* sanity checks */
	assert(cinfo->btype != BT_NONE);

	/* set all the vital stuff */
	cirrusfb_set_fbinfo(info);

	dev_dbg(info->device, "(RAM start set to: 0x%p)\n", info->screen_base);

	err = fb_find_mode(&info->var, info, mode_option, NULL, 0, NULL, 8);
	if (!err) {
		dev_dbg(info->device, "wrong initial video mode\n");
		err = -EINVAL;
		goto err_dealloc_cmap;
	}

	info->var.activate = FB_ACTIVATE_NOW;

	err = cirrusfb_check_var(&info->var, info);
	if (err < 0) {
		/* should never happen */
		dev_dbg(info->device,
			"choking on default var... umm, no good.\n");
		goto err_dealloc_cmap;
	}

	err = register_framebuffer(info);
	if (err < 0) {
		dev_err(info->device,
			"could not register fb device; err = %d!\n", err);
		goto err_dealloc_cmap;
	}

	return 0;

err_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);
	return err;
}