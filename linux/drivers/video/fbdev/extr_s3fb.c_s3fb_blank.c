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
struct TYPE_2__ {int /*<<< orphan*/  vgabase; } ;
struct s3fb_info {TYPE_1__ state; } ;
struct fb_info {struct s3fb_info* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  fb_dbg (struct fb_info*,char*) ; 
 int /*<<< orphan*/  svga_wcrt_mask (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  svga_wseq_mask (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int s3fb_blank(int blank_mode, struct fb_info *info)
{
	struct s3fb_info *par = info->par;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		fb_dbg(info, "unblank\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x00, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x00, 0x20);
		break;
	case FB_BLANK_NORMAL:
		fb_dbg(info, "blank\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x00, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		fb_dbg(info, "hsync\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x02, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		fb_dbg(info, "vsync\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x04, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		break;
	case FB_BLANK_POWERDOWN:
		fb_dbg(info, "sync down\n");
		svga_wcrt_mask(par->state.vgabase, 0x56, 0x06, 0x06);
		svga_wseq_mask(par->state.vgabase, 0x01, 0x20, 0x20);
		break;
	}

	return 0;
}