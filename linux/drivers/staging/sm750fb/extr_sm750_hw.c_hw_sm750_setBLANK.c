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
struct lynxfb_output {int paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_DISPLAY_CTRL ; 
 unsigned int CRT_DISPLAY_CTRL_BLANK ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  PANEL_DISPLAY_CTRL ; 
 unsigned int PANEL_DISPLAY_CTRL_DATA ; 
 int /*<<< orphan*/  SYSTEM_CTRL ; 
 unsigned int SYSTEM_CTRL_DPMS_MASK ; 
 unsigned int SYSTEM_CTRL_DPMS_VNHN ; 
 unsigned int SYSTEM_CTRL_DPMS_VNHP ; 
 unsigned int SYSTEM_CTRL_DPMS_VPHN ; 
 unsigned int SYSTEM_CTRL_DPMS_VPHP ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int sm750_crt ; 
 int sm750_panel ; 

int hw_sm750_setBLANK(struct lynxfb_output *output, int blank)
{
	unsigned int dpms, pps, crtdb;

	dpms = 0;
	pps = 0;
	crtdb = 0;

	switch (blank) {
	case FB_BLANK_UNBLANK:
		pr_debug("flag = FB_BLANK_UNBLANK\n");
		dpms = SYSTEM_CTRL_DPMS_VPHP;
		pps = PANEL_DISPLAY_CTRL_DATA;
		break;
	case FB_BLANK_NORMAL:
		pr_debug("flag = FB_BLANK_NORMAL\n");
		dpms = SYSTEM_CTRL_DPMS_VPHP;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		dpms = SYSTEM_CTRL_DPMS_VNHP;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		dpms = SYSTEM_CTRL_DPMS_VPHN;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	case FB_BLANK_POWERDOWN:
		dpms = SYSTEM_CTRL_DPMS_VNHN;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	}

	if (output->paths & sm750_crt) {
		unsigned int val = peek32(SYSTEM_CTRL) & ~SYSTEM_CTRL_DPMS_MASK;

		poke32(SYSTEM_CTRL, val | dpms);

		val = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_BLANK;
		poke32(CRT_DISPLAY_CTRL, val | crtdb);
	}

	if (output->paths & sm750_panel) {
		unsigned int val = peek32(PANEL_DISPLAY_CTRL);

		val &= ~PANEL_DISPLAY_CTRL_DATA;
		val |= pps;
		poke32(PANEL_DISPLAY_CTRL, val);
	}

	return 0;
}