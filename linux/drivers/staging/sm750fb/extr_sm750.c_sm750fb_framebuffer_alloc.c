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
struct sm750_dev {int /*<<< orphan*/  fb_count; struct fb_info** fbinfo; TYPE_1__* pdev; } ;
struct lynxfb_par {struct sm750_dev* dev; } ;
struct fb_info {struct lynxfb_par* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int lynxfb_set_fbinfo (struct fb_info*,int) ; 
 int register_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int sm750fb_framebuffer_alloc(struct sm750_dev *sm750_dev, int fbidx)
{
	struct fb_info *fb_info;
	struct lynxfb_par *par;
	int err;

	fb_info = framebuffer_alloc(sizeof(struct lynxfb_par),
				    &sm750_dev->pdev->dev);
	if (!fb_info)
		return -ENOMEM;

	sm750_dev->fbinfo[fbidx] = fb_info;
	par = fb_info->par;
	par->dev = sm750_dev;

	err = lynxfb_set_fbinfo(fb_info, fbidx);
	if (err)
		goto release_fb;

	err = register_framebuffer(fb_info);
	if (err < 0)
		goto release_fb;

	sm750_dev->fb_count++;

	return 0;

release_fb:
	framebuffer_release(fb_info);
	return err;
}