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
struct TYPE_2__ {int /*<<< orphan*/  visual; } ;
struct fb_info {int /*<<< orphan*/  cmap; TYPE_1__ fix; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_STATIC_PSEUDOCOLOR ; 
 int /*<<< orphan*/  fb_set_cmap (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  vt8500lcd_setcolreg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fb_info*) ; 

__attribute__((used)) static int vt8500lcd_blank(int blank, struct fb_info *info)
{
	int i;

	switch (blank) {
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
		if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    info->fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			for (i = 0; i < 256; i++)
				vt8500lcd_setcolreg(i, 0, 0, 0, 0, info);
	case FB_BLANK_UNBLANK:
		if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    info->fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			fb_set_cmap(&info->cmap, info);
	}
	return 0;
}