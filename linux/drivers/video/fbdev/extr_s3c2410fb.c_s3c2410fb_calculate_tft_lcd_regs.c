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
struct s3c2410fb_info {int /*<<< orphan*/  dev; } ;
struct s3c2410fb_hw {int lcdcon5; int lcdcon2; int lcdcon3; int /*<<< orphan*/  lcdcon4; int /*<<< orphan*/  lcdcon1; } ;
struct fb_var_screeninfo {int bits_per_pixel; scalar_t__ hsync_len; scalar_t__ xres; scalar_t__ left_margin; scalar_t__ right_margin; scalar_t__ vsync_len; scalar_t__ lower_margin; scalar_t__ upper_margin; scalar_t__ yres; } ;
struct fb_info {struct fb_var_screeninfo var; struct s3c2410fb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_LCDCON1_TFT16BPP ; 
 int /*<<< orphan*/  S3C2410_LCDCON1_TFT1BPP ; 
 int /*<<< orphan*/  S3C2410_LCDCON1_TFT24BPP ; 
 int /*<<< orphan*/  S3C2410_LCDCON1_TFT2BPP ; 
 int /*<<< orphan*/  S3C2410_LCDCON1_TFT4BPP ; 
 int /*<<< orphan*/  S3C2410_LCDCON1_TFT8BPP ; 
 int S3C2410_LCDCON2_LINEVAL (scalar_t__) ; 
 int S3C2410_LCDCON2_VBPD (scalar_t__) ; 
 int S3C2410_LCDCON2_VFPD (scalar_t__) ; 
 int S3C2410_LCDCON2_VSPW (scalar_t__) ; 
 int S3C2410_LCDCON3_HBPD (scalar_t__) ; 
 int S3C2410_LCDCON3_HFPD (scalar_t__) ; 
 int S3C2410_LCDCON3_HOZVAL (scalar_t__) ; 
 int /*<<< orphan*/  S3C2410_LCDCON4_HSPW (scalar_t__) ; 
 int S3C2410_LCDCON5_BPP24BL ; 
 int S3C2410_LCDCON5_BSWP ; 
 int S3C2410_LCDCON5_FRM565 ; 
 int S3C2410_LCDCON5_HWSWP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void s3c2410fb_calculate_tft_lcd_regs(const struct fb_info *info,
					     struct s3c2410fb_hw *regs)
{
	const struct s3c2410fb_info *fbi = info->par;
	const struct fb_var_screeninfo *var = &info->var;

	switch (var->bits_per_pixel) {
	case 1:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT1BPP;
		break;
	case 2:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT2BPP;
		break;
	case 4:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT4BPP;
		break;
	case 8:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT8BPP;
		regs->lcdcon5 |= S3C2410_LCDCON5_BSWP |
				 S3C2410_LCDCON5_FRM565;
		regs->lcdcon5 &= ~S3C2410_LCDCON5_HWSWP;
		break;
	case 16:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT16BPP;
		regs->lcdcon5 &= ~S3C2410_LCDCON5_BSWP;
		regs->lcdcon5 |= S3C2410_LCDCON5_HWSWP;
		break;
	case 32:
		regs->lcdcon1 |= S3C2410_LCDCON1_TFT24BPP;
		regs->lcdcon5 &= ~(S3C2410_LCDCON5_BSWP |
				   S3C2410_LCDCON5_HWSWP |
				   S3C2410_LCDCON5_BPP24BL);
		break;
	default:
		/* invalid pixel depth */
		dev_err(fbi->dev, "invalid bpp %d\n",
			var->bits_per_pixel);
	}
	/* update X/Y info */
	dprintk("setting vert: up=%d, low=%d, sync=%d\n",
		var->upper_margin, var->lower_margin, var->vsync_len);

	dprintk("setting horz: lft=%d, rt=%d, sync=%d\n",
		var->left_margin, var->right_margin, var->hsync_len);

	regs->lcdcon2 = S3C2410_LCDCON2_LINEVAL(var->yres - 1) |
			S3C2410_LCDCON2_VBPD(var->upper_margin - 1) |
			S3C2410_LCDCON2_VFPD(var->lower_margin - 1) |
			S3C2410_LCDCON2_VSPW(var->vsync_len - 1);

	regs->lcdcon3 = S3C2410_LCDCON3_HBPD(var->right_margin - 1) |
			S3C2410_LCDCON3_HFPD(var->left_margin - 1) |
			S3C2410_LCDCON3_HOZVAL(var->xres - 1);

	regs->lcdcon4 = S3C2410_LCDCON4_HSPW(var->hsync_len - 1);
}