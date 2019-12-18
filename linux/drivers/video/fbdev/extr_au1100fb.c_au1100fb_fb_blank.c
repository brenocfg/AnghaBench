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
struct fb_info {int dummy; } ;
struct au1100fb_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  lcd_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_CONTROL_GO ; 
#define  VESA_HSYNC_SUSPEND 131 
#define  VESA_NO_BLANKING 130 
#define  VESA_POWERDOWN 129 
#define  VESA_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  print_dbg (char*,int,struct fb_info*) ; 
 struct au1100fb_device* to_au1100fb_device (struct fb_info*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1100fb_fb_blank(int blank_mode, struct fb_info *fbi)
{
	struct au1100fb_device *fbdev = to_au1100fb_device(fbi);

	print_dbg("fb_blank %d %p", blank_mode, fbi);

	switch (blank_mode) {

	case VESA_NO_BLANKING:
		/* Turn on panel */
		fbdev->regs->lcd_control |= LCD_CONTROL_GO;
		wmb(); /* drain writebuffer */
		break;

	case VESA_VSYNC_SUSPEND:
	case VESA_HSYNC_SUSPEND:
	case VESA_POWERDOWN:
		/* Turn off panel */
		fbdev->regs->lcd_control &= ~LCD_CONTROL_GO;
		wmb(); /* drain writebuffer */
		break;
	default:
		break;

	}
	return 0;
}