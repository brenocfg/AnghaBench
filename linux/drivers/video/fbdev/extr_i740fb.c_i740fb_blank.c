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
struct i740fb_par {int dummy; } ;
struct fb_info {struct i740fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMS_SYNC_SELECT ; 
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int HSYNC_OFF ; 
 int HSYNC_ON ; 
 scalar_t__ SRX ; 
 int VSYNC_OFF ; 
 int VSYNC_ON ; 
 int /*<<< orphan*/  XRX ; 
 int i740inb (struct i740fb_par*,scalar_t__) ; 
 int /*<<< orphan*/  i740outb (struct i740fb_par*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  i740outreg (struct i740fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i740fb_blank(int blank_mode, struct fb_info *info)
{
	struct i740fb_par *par = info->par;

	unsigned char SEQ01;
	int DPMSSyncSelect;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		SEQ01 = 0x00;
		DPMSSyncSelect = HSYNC_ON | VSYNC_ON;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		SEQ01 = 0x20;
		DPMSSyncSelect = HSYNC_ON | VSYNC_OFF;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		SEQ01 = 0x20;
		DPMSSyncSelect = HSYNC_OFF | VSYNC_ON;
		break;
	case FB_BLANK_POWERDOWN:
		SEQ01 = 0x20;
		DPMSSyncSelect = HSYNC_OFF | VSYNC_OFF;
		break;
	default:
		return -EINVAL;
	}
	/* Turn the screen on/off */
	i740outb(par, SRX, 0x01);
	SEQ01 |= i740inb(par, SRX + 1) & ~0x20;
	i740outb(par, SRX, 0x01);
	i740outb(par, SRX + 1, SEQ01);

	/* Set the DPMS mode */
	i740outreg(par, XRX, DPMS_SYNC_SELECT, DPMSSyncSelect);

	/* Let fbcon do a soft blank for us */
	return (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
}