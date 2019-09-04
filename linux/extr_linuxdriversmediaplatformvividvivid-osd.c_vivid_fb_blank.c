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
struct vivid_dev {int dummy; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*,int) ; 

__attribute__((used)) static int vivid_fb_blank(int blank_mode, struct fb_info *info)
{
	struct vivid_dev *dev = (struct vivid_dev *)info->par;

	dprintk(dev, 1, "Set blanking mode : %d\n", blank_mode);
	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		break;
	case FB_BLANK_NORMAL:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_POWERDOWN:
		break;
	}
	return 0;
}