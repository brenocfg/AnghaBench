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
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct fb_info {int /*<<< orphan*/  pseudo_palette; TYPE_1__ cmap; } ;
struct au1200fb_platdata {int dummy; } ;

/* Variables and functions */
 struct fb_info** _au1200fb_infos ; 
 int /*<<< orphan*/  au1200_setpanel (int /*<<< orphan*/ *,struct au1200fb_platdata*) ; 
 int device_count ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_1__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct au1200fb_platdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int au1200fb_drv_remove(struct platform_device *dev)
{
	struct au1200fb_platdata *pd = platform_get_drvdata(dev);
	struct fb_info *fbi;
	int plane;

	/* Turn off the panel */
	au1200_setpanel(NULL, pd);

	for (plane = 0; plane < device_count; ++plane)	{
		fbi = _au1200fb_infos[plane];

		/* Clean up all probe data */
		unregister_framebuffer(fbi);
		if (fbi->cmap.len != 0)
			fb_dealloc_cmap(&fbi->cmap);
		kfree(fbi->pseudo_palette);

		framebuffer_release(fbi);
		_au1200fb_infos[plane] = NULL;
	}

	free_irq(platform_get_irq(dev, 0), (void *)dev);

	return 0;
}