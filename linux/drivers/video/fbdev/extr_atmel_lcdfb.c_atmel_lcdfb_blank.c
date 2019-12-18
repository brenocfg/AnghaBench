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
struct fb_info {struct atmel_lcdfb_info* par; } ;
struct atmel_lcdfb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  atmel_lcdfb_start (struct atmel_lcdfb_info*) ; 
 int /*<<< orphan*/  atmel_lcdfb_stop (struct atmel_lcdfb_info*) ; 

__attribute__((used)) static int atmel_lcdfb_blank(int blank_mode, struct fb_info *info)
{
	struct atmel_lcdfb_info *sinfo = info->par;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		atmel_lcdfb_start(sinfo);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
		break;
	case FB_BLANK_POWERDOWN:
		atmel_lcdfb_stop(sinfo);
		break;
	default:
		return -EINVAL;
	}

	/* let fbcon do a soft blank for us */
	return ((blank_mode == FB_BLANK_NORMAL) ? 1 : 0);
}