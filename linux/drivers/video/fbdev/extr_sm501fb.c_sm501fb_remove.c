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
struct sm501fb_info {struct fb_info** fb; } ;
struct platform_device {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD_CRT ; 
 int /*<<< orphan*/  HEAD_PANEL ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (struct sm501fb_info*) ; 
 struct sm501fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sm501_free_init_fb (struct sm501fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501fb_stop (struct sm501fb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int sm501fb_remove(struct platform_device *pdev)
{
	struct sm501fb_info *info = platform_get_drvdata(pdev);
	struct fb_info	   *fbinfo_crt = info->fb[0];
	struct fb_info	   *fbinfo_pnl = info->fb[1];

	sm501_free_init_fb(info, HEAD_CRT);
	sm501_free_init_fb(info, HEAD_PANEL);

	if (fbinfo_crt)
		unregister_framebuffer(fbinfo_crt);
	if (fbinfo_pnl)
		unregister_framebuffer(fbinfo_pnl);

	sm501fb_stop(info);
	kfree(info);

	framebuffer_release(fbinfo_pnl);
	framebuffer_release(fbinfo_crt);

	return 0;
}