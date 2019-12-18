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
struct gxt4500_par {int dummy; } ;
struct fb_info {struct gxt4500_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_CTL ; 
 int DISP_CTL_OFF ; 
#define  FB_BLANK_HSYNC_SUSPEND 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  SYNC_CTL ; 
 int SYNC_CTL_HSYNC_OFF ; 
 int SYNC_CTL_SYNC_OFF ; 
 int SYNC_CTL_VSYNC_OFF ; 
 int readreg (struct gxt4500_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writereg (struct gxt4500_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gxt4500_blank(int blank, struct fb_info *info)
{
	struct gxt4500_par *par = info->par;
	int ctrl, dctl;

	ctrl = readreg(par, SYNC_CTL);
	ctrl &= ~(SYNC_CTL_SYNC_OFF | SYNC_CTL_HSYNC_OFF | SYNC_CTL_VSYNC_OFF);
	dctl = readreg(par, DISP_CTL);
	dctl |= DISP_CTL_OFF;
	switch (blank) {
	case FB_BLANK_UNBLANK:
		dctl &= ~DISP_CTL_OFF;
		break;
	case FB_BLANK_POWERDOWN:
		ctrl |= SYNC_CTL_SYNC_OFF;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		ctrl |= SYNC_CTL_HSYNC_OFF;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		ctrl |= SYNC_CTL_VSYNC_OFF;
		break;
	default: ;
	}
	writereg(par, SYNC_CTL, ctrl);
	writereg(par, DISP_CTL, dctl);

	return 0;
}