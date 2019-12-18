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
struct riva_par {int dummy; } ;
struct fb_info {struct riva_par* par; } ;

/* Variables and functions */
 int CRTCin (struct riva_par*,int) ; 
 int /*<<< orphan*/  CRTCout (struct riva_par*,int,unsigned char) ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int SEQin (struct riva_par*,int) ; 
 int /*<<< orphan*/  SEQout (struct riva_par*,int,unsigned char) ; 

__attribute__((used)) static int rivafb_blank(int blank, struct fb_info *info)
{
	struct riva_par *par= info->par;
	unsigned char tmp, vesa;

	tmp = SEQin(par, 0x01) & ~0x20;	/* screen on/off */
	vesa = CRTCin(par, 0x1a) & ~0xc0;	/* sync on/off */

	NVTRACE_ENTER();

	if (blank)
		tmp |= 0x20;

	switch (blank) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		vesa |= 0x80;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		vesa |= 0x40;
		break;
	case FB_BLANK_POWERDOWN:
		vesa |= 0xc0;
		break;
	}

	SEQout(par, 0x01, tmp);
	CRTCout(par, 0x1a, vesa);

	NVTRACE_LEAVE();

	return 0;
}