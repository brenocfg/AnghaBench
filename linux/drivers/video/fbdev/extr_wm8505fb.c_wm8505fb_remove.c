#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {TYPE_2__ cmap; } ;
struct wm8505fb_info {TYPE_1__ fb; int /*<<< orphan*/  regbase; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 struct wm8505fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8505fb_remove(struct platform_device *pdev)
{
	struct wm8505fb_info *fbi = platform_get_drvdata(pdev);

	unregister_framebuffer(&fbi->fb);

	writel(0, fbi->regbase);

	if (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);

	return 0;
}