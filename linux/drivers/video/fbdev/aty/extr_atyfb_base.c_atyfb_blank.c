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
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {scalar_t__ lcd_table; scalar_t__ asleep; scalar_t__ lock_blank; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  LCD_GEN_CNTL ; 
 int LCD_ON ; 
 int /*<<< orphan*/  POWER_MANAGEMENT ; 
 int PWR_BLON ; 
 int aty_ld_lcd (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_lcd (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 

__attribute__((used)) static int atyfb_blank(int blank, struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 gen_cntl;

	if (par->lock_blank || par->asleep)
		return 0;

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table && blank > FB_BLANK_NORMAL &&
	    (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) {
		u32 pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		pm &= ~PWR_BLON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
	}
#endif

	gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);
	gen_cntl &= ~0x400004c;
	switch (blank) {
	case FB_BLANK_UNBLANK:
		break;
	case FB_BLANK_NORMAL:
		gen_cntl |= 0x4000040;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		gen_cntl |= 0x4000048;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		gen_cntl |= 0x4000044;
		break;
	case FB_BLANK_POWERDOWN:
		gen_cntl |= 0x400004c;
		break;
	}
	aty_st_le32(CRTC_GEN_CNTL, gen_cntl, par);

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table && blank <= FB_BLANK_NORMAL &&
	    (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) {
		u32 pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		pm |= PWR_BLON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
	}
#endif

	return 0;
}