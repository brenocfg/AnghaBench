#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct neofb_par {int PanelDispCntlRegRead; int PanelDispCntlReg1; int /*<<< orphan*/  state; } ;
struct fb_info {struct neofb_par* par; } ;
struct TYPE_3__ {int eax; int ebx; int ecx; } ;
typedef  TYPE_1__ SMMRegisters ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int NEO_GR01_SUPPRESS_HSYNC ; 
 int NEO_GR01_SUPPRESS_VSYNC ; 
 int VGA_SR01_SCREEN_OFF ; 
 int /*<<< orphan*/  neoLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neoUnlock () ; 
 int /*<<< orphan*/  tosh_smm (TYPE_1__*) ; 
 int vga_rgfx (int /*<<< orphan*/ *,int) ; 
 int vga_rseq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int neofb_blank(int blank_mode, struct fb_info *info)
{
	/*
	 *  Blank the screen if blank_mode != 0, else unblank.
	 *  Return 0 if blanking succeeded, != 0 if un-/blanking failed due to
	 *  e.g. a video mode which doesn't support it. Implements VESA suspend
	 *  and powerdown modes for monitors, and backlight control on LCDs.
	 *    blank_mode == 0: unblanked (backlight on)
	 *    blank_mode == 1: blank (backlight on)
	 *    blank_mode == 2: suspend vsync (backlight off)
	 *    blank_mode == 3: suspend hsync (backlight off)
	 *    blank_mode == 4: powerdown (backlight off)
	 *
	 *  wms...Enable VESA DPMS compatible powerdown mode
	 *  run "setterm -powersave powerdown" to take advantage
	 */
	struct neofb_par *par = info->par;
	int seqflags, lcdflags, dpmsflags, reg, tmpdisp;

	/*
	 * Read back the register bits related to display configuration. They might
	 * have been changed underneath the driver via Fn key stroke.
	 */
	neoUnlock();
	tmpdisp = vga_rgfx(NULL, 0x20) & 0x03;
	neoLock(&par->state);

	/* In case we blank the screen, we want to store the possibly new
	 * configuration in the driver. During un-blank, we re-apply this setting,
	 * since the LCD bit will be cleared in order to switch off the backlight.
	 */
	if (par->PanelDispCntlRegRead) {
		par->PanelDispCntlReg1 = tmpdisp;
	}
	par->PanelDispCntlRegRead = !blank_mode;

	switch (blank_mode) {
	case FB_BLANK_POWERDOWN:	/* powerdown - both sync lines down */
		seqflags = VGA_SR01_SCREEN_OFF; /* Disable sequencer */
		lcdflags = 0;			/* LCD off */
		dpmsflags = NEO_GR01_SUPPRESS_HSYNC |
			    NEO_GR01_SUPPRESS_VSYNC;
#ifdef CONFIG_TOSHIBA
		/* Do we still need this ? */
		/* attempt to turn off backlight on toshiba; also turns off external */
		{
			SMMRegisters regs;

			regs.eax = 0xff00; /* HCI_SET */
			regs.ebx = 0x0002; /* HCI_BACKLIGHT */
			regs.ecx = 0x0000; /* HCI_DISABLE */
			tosh_smm(&regs);
		}
#endif
		break;
	case FB_BLANK_HSYNC_SUSPEND:		/* hsync off */
		seqflags = VGA_SR01_SCREEN_OFF;	/* Disable sequencer */
		lcdflags = 0;			/* LCD off */
		dpmsflags = NEO_GR01_SUPPRESS_HSYNC;
		break;
	case FB_BLANK_VSYNC_SUSPEND:		/* vsync off */
		seqflags = VGA_SR01_SCREEN_OFF;	/* Disable sequencer */
		lcdflags = 0;			/* LCD off */
		dpmsflags = NEO_GR01_SUPPRESS_VSYNC;
		break;
	case FB_BLANK_NORMAL:		/* just blank screen (backlight stays on) */
		seqflags = VGA_SR01_SCREEN_OFF;	/* Disable sequencer */
		/*
		 * During a blank operation with the LID shut, we might store "LCD off"
		 * by mistake. Due to timing issues, the BIOS may switch the lights
		 * back on, and we turn it back off once we "unblank".
		 *
		 * So here is an attempt to implement ">=" - if we are in the process
		 * of unblanking, and the LCD bit is unset in the driver but set in the
		 * register, we must keep it.
		 */
		lcdflags = ((par->PanelDispCntlReg1 | tmpdisp) & 0x02); /* LCD normal */
		dpmsflags = 0x00;	/* no hsync/vsync suppression */
		break;
	case FB_BLANK_UNBLANK:		/* unblank */
		seqflags = 0;			/* Enable sequencer */
		lcdflags = ((par->PanelDispCntlReg1 | tmpdisp) & 0x02); /* LCD normal */
		dpmsflags = 0x00;	/* no hsync/vsync suppression */
#ifdef CONFIG_TOSHIBA
		/* Do we still need this ? */
		/* attempt to re-enable backlight/external on toshiba */
		{
			SMMRegisters regs;

			regs.eax = 0xff00; /* HCI_SET */
			regs.ebx = 0x0002; /* HCI_BACKLIGHT */
			regs.ecx = 0x0001; /* HCI_ENABLE */
			tosh_smm(&regs);
		}
#endif
		break;
	default:	/* Anything else we don't understand; return 1 to tell
			 * fb_blank we didn't aactually do anything */
		return 1;
	}

	neoUnlock();
	reg = (vga_rseq(NULL, 0x01) & ~0x20) | seqflags;
	vga_wseq(NULL, 0x01, reg);
	reg = (vga_rgfx(NULL, 0x20) & ~0x02) | lcdflags;
	vga_wgfx(NULL, 0x20, reg);
	reg = (vga_rgfx(NULL, 0x01) & ~0xF0) | 0x80 | dpmsflags;
	vga_wgfx(NULL, 0x01, reg);
	neoLock(&par->state);
	return 0;
}