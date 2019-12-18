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
struct fb_info {struct da8xx_fb_par* par; } ;
struct da8xx_fb_par {int blank; int /*<<< orphan*/  lcd_supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA8XX_FRAME_WAIT ; 
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  lcd_disable_raster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_enable_raster () ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfb_blank(int blank, struct fb_info *info)
{
	struct da8xx_fb_par *par = info->par;
	int ret = 0;

	if (par->blank == blank)
		return 0;

	par->blank = blank;
	switch (blank) {
	case FB_BLANK_UNBLANK:
		lcd_enable_raster();

		if (par->lcd_supply) {
			ret = regulator_enable(par->lcd_supply);
			if (ret)
				return ret;
		}
		break;
	case FB_BLANK_NORMAL:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_POWERDOWN:
		if (par->lcd_supply) {
			ret = regulator_disable(par->lcd_supply);
			if (ret)
				return ret;
		}

		lcd_disable_raster(DA8XX_FRAME_WAIT);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}