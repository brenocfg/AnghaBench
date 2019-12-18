#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct sa1100fb_lcd_reg {int lccr0; int lccr1; int lccr2; int lccr3; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ fix; } ;
struct sa1100fb_info {scalar_t__ dbar1; scalar_t__ palette_dma; scalar_t__ dbar2; scalar_t__ screen_dma; int reg_lccr0; int reg_lccr1; int reg_lccr2; int reg_lccr3; scalar_t__ base; int /*<<< orphan*/  dev; TYPE_3__* inf; TYPE_2__ fb; } ;
struct fb_var_screeninfo {int xres; int hsync_len; int left_margin; int right_margin; int yres; int vsync_len; int upper_margin; int lower_margin; int sync; int bits_per_pixel; int /*<<< orphan*/  pixclock; } ;
struct TYPE_6__ {int lccr0; int lccr3; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_REENABLE ; 
 scalar_t__ DBAR1 ; 
 scalar_t__ DBAR2 ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 scalar_t__ LCCR0 ; 
 int LCCR0_BAM ; 
 int LCCR0_DMADel (int /*<<< orphan*/ ) ; 
 int LCCR0_Dual ; 
 int LCCR0_ERM ; 
 int LCCR0_LDM ; 
 int LCCR0_LEN ; 
 int LCCR0_LtlEnd ; 
 scalar_t__ LCCR1 ; 
 int LCCR1_BegLnDel (int) ; 
 int LCCR1_DisWdth (int) ; 
 int LCCR1_EndLnDel (int) ; 
 int LCCR1_HorSnchWdth (int) ; 
 scalar_t__ LCCR2 ; 
 int LCCR2_BegFrmDel (int) ; 
 int LCCR2_DisHght (int) ; 
 int LCCR2_EndFrmDel (int) ; 
 int LCCR2_VrtSnchWdth (int) ; 
 scalar_t__ LCCR3 ; 
 int LCCR3_HorSnchH ; 
 int LCCR3_HorSnchL ; 
 int LCCR3_PixClkDiv (int) ; 
 int LCCR3_VrtSnchH ; 
 int LCCR3_VrtSnchL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int get_pcd (struct sa1100fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sa1100fb_schedule_work (struct sa1100fb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100fb_activate_var(struct fb_var_screeninfo *var, struct sa1100fb_info *fbi)
{
	struct sa1100fb_lcd_reg new_regs;
	u_int half_screen_size, yres, pcd;
	u_long flags;

	dev_dbg(fbi->dev, "Configuring SA1100 LCD\n");

	dev_dbg(fbi->dev, "var: xres=%d hslen=%d lm=%d rm=%d\n",
		var->xres, var->hsync_len,
		var->left_margin, var->right_margin);
	dev_dbg(fbi->dev, "var: yres=%d vslen=%d um=%d bm=%d\n",
		var->yres, var->vsync_len,
		var->upper_margin, var->lower_margin);

#if DEBUG_VAR
	if (var->xres < 16        || var->xres > 1024)
		dev_err(fbi->dev, "%s: invalid xres %d\n",
			fbi->fb.fix.id, var->xres);
	if (var->hsync_len < 1    || var->hsync_len > 64)
		dev_err(fbi->dev, "%s: invalid hsync_len %d\n",
			fbi->fb.fix.id, var->hsync_len);
	if (var->left_margin < 1  || var->left_margin > 255)
		dev_err(fbi->dev, "%s: invalid left_margin %d\n",
			fbi->fb.fix.id, var->left_margin);
	if (var->right_margin < 1 || var->right_margin > 255)
		dev_err(fbi->dev, "%s: invalid right_margin %d\n",
			fbi->fb.fix.id, var->right_margin);
	if (var->yres < 1         || var->yres > 1024)
		dev_err(fbi->dev, "%s: invalid yres %d\n",
			fbi->fb.fix.id, var->yres);
	if (var->vsync_len < 1    || var->vsync_len > 64)
		dev_err(fbi->dev, "%s: invalid vsync_len %d\n",
			fbi->fb.fix.id, var->vsync_len);
	if (var->upper_margin < 0 || var->upper_margin > 255)
		dev_err(fbi->dev, "%s: invalid upper_margin %d\n",
			fbi->fb.fix.id, var->upper_margin);
	if (var->lower_margin < 0 || var->lower_margin > 255)
		dev_err(fbi->dev, "%s: invalid lower_margin %d\n",
			fbi->fb.fix.id, var->lower_margin);
#endif

	new_regs.lccr0 = fbi->inf->lccr0 |
		LCCR0_LEN | LCCR0_LDM | LCCR0_BAM |
		LCCR0_ERM | LCCR0_LtlEnd | LCCR0_DMADel(0);

	new_regs.lccr1 =
		LCCR1_DisWdth(var->xres) +
		LCCR1_HorSnchWdth(var->hsync_len) +
		LCCR1_BegLnDel(var->left_margin) +
		LCCR1_EndLnDel(var->right_margin);

	/*
	 * If we have a dual scan LCD, then we need to halve
	 * the YRES parameter.
	 */
	yres = var->yres;
	if (fbi->inf->lccr0 & LCCR0_Dual)
		yres /= 2;

	new_regs.lccr2 =
		LCCR2_DisHght(yres) +
		LCCR2_VrtSnchWdth(var->vsync_len) +
		LCCR2_BegFrmDel(var->upper_margin) +
		LCCR2_EndFrmDel(var->lower_margin);

	pcd = get_pcd(fbi, var->pixclock);
	new_regs.lccr3 = LCCR3_PixClkDiv(pcd) | fbi->inf->lccr3 |
		(var->sync & FB_SYNC_HOR_HIGH_ACT ? LCCR3_HorSnchH : LCCR3_HorSnchL) |
		(var->sync & FB_SYNC_VERT_HIGH_ACT ? LCCR3_VrtSnchH : LCCR3_VrtSnchL);

	dev_dbg(fbi->dev, "nlccr0 = 0x%08lx\n", new_regs.lccr0);
	dev_dbg(fbi->dev, "nlccr1 = 0x%08lx\n", new_regs.lccr1);
	dev_dbg(fbi->dev, "nlccr2 = 0x%08lx\n", new_regs.lccr2);
	dev_dbg(fbi->dev, "nlccr3 = 0x%08lx\n", new_regs.lccr3);

	half_screen_size = var->bits_per_pixel;
	half_screen_size = half_screen_size * var->xres * var->yres / 16;

	/* Update shadow copy atomically */
	local_irq_save(flags);
	fbi->dbar1 = fbi->palette_dma;
	fbi->dbar2 = fbi->screen_dma + half_screen_size;

	fbi->reg_lccr0 = new_regs.lccr0;
	fbi->reg_lccr1 = new_regs.lccr1;
	fbi->reg_lccr2 = new_regs.lccr2;
	fbi->reg_lccr3 = new_regs.lccr3;
	local_irq_restore(flags);

	/*
	 * Only update the registers if the controller is enabled
	 * and something has changed.
	 */
	if (readl_relaxed(fbi->base + LCCR0) != fbi->reg_lccr0 ||
	    readl_relaxed(fbi->base + LCCR1) != fbi->reg_lccr1 ||
	    readl_relaxed(fbi->base + LCCR2) != fbi->reg_lccr2 ||
	    readl_relaxed(fbi->base + LCCR3) != fbi->reg_lccr3 ||
	    readl_relaxed(fbi->base + DBAR1) != fbi->dbar1 ||
	    readl_relaxed(fbi->base + DBAR2) != fbi->dbar2)
		sa1100fb_schedule_work(fbi, C_REENABLE);

	return 0;
}