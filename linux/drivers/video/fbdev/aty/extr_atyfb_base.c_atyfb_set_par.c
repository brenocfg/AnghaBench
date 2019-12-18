#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fb_var_screeninfo {int bits_per_pixel; int accel_flags; scalar_t__ xres; scalar_t__ hsync_len; scalar_t__ left_margin; scalar_t__ yres; scalar_t__ lower_margin; scalar_t__ vsync_len; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  yres_virtual; } ;
struct TYPE_8__ {int /*<<< orphan*/  smem_start; int /*<<< orphan*/  visual; int /*<<< orphan*/  line_length; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  flags; TYPE_2__* fbops; struct fb_var_screeninfo var; scalar_t__ par; } ;
struct TYPE_12__ {int gen_cntl; int h_tot_disp; int v_tot_disp; int vxres; } ;
struct atyfb_par {int accel_flags; int mem_refresh_rate; scalar_t__ lcd_table; TYPE_5__ crtc; scalar_t__ aux_start; int /*<<< orphan*/  pll; TYPE_4__* pll_ops; TYPE_3__* dac_ops; scalar_t__ blitter_may_be_busy; scalar_t__ asleep; } ;
typedef  int /*<<< orphan*/  debug ;
struct TYPE_11__ {int (* var_to_pll ) (struct fb_info*,scalar_t__,int,int /*<<< orphan*/ *) ;scalar_t__ (* pll_to_var ) (struct fb_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_pll ) (struct fb_info*,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* set_dac ) (struct fb_info*,int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/ * fb_sync; } ;

/* Variables and functions */
 int BUS_APER_REG_DIS ; 
 int BUS_CNTL ; 
 int CRTC_DBL_SCAN_EN ; 
 int CRTC_INTERLACE_EN ; 
 int /*<<< orphan*/  CT_BUS ; 
 int DAC_CNTL ; 
 int /*<<< orphan*/  DAC_MASK ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int EXT_MEM_CNTL ; 
 int EXT_VERT_STRETCH ; 
 int /*<<< orphan*/  FBINFO_HWACCEL_DISABLED ; 
 int FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  INTEGRATED ; 
 int /*<<< orphan*/  LT_LCD_REGS ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_POSTDIV ; 
 int MEM_CNTL ; 
 int /*<<< orphan*/  MOBIL_BUS ; 
 int POWER_MANAGEMENT ; 
 int /*<<< orphan*/  PRINTKE (char*) ; 
 int /*<<< orphan*/  VT_BUS ; 
 int /*<<< orphan*/  aty_crtc_to_var (TYPE_5__*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  aty_init_engine (struct atyfb_par*,struct fb_info*) ; 
 int /*<<< orphan*/  aty_ld_lcd (int,struct atyfb_par*) ; 
 int aty_ld_le32 (int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_ld_pll_ct (int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_set_crtc (struct atyfb_par*,TYPE_5__*) ; 
 int /*<<< orphan*/  aty_st_8 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int,scalar_t__,struct atyfb_par*) ; 
 int aty_var_to_crtc (struct fb_info*,struct fb_var_screeninfo*,TYPE_5__*) ; 
 scalar_t__ atyfb_get_pixclock (struct fb_var_screeninfo*,struct atyfb_par*) ; 
 int /*<<< orphan*/ * atyfb_sync ; 
 int /*<<< orphan*/  btext_update_display (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  calc_line_length (struct atyfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lt_lcd_regs ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int stub1 (struct fb_info*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct fb_info*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub3 (struct fb_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct fb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_idle (struct atyfb_par*) ; 

__attribute__((used)) static int atyfb_set_par(struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	struct fb_var_screeninfo *var = &info->var;
	u32 tmp, pixclock;
	int err;
#ifdef DEBUG
	struct fb_var_screeninfo debug;
	u32 pixclock_in_ps;
#endif
	if (par->asleep)
		return 0;

	err = aty_var_to_crtc(info, var, &par->crtc);
	if (err)
		return err;

	pixclock = atyfb_get_pixclock(var, par);

	if (pixclock == 0) {
		PRINTKE("Invalid pixclock\n");
		return -EINVAL;
	} else {
		err = par->pll_ops->var_to_pll(info, pixclock,
					       var->bits_per_pixel, &par->pll);
		if (err)
			return err;
	}

	par->accel_flags = var->accel_flags; /* hack */

	if (var->accel_flags) {
		info->fbops->fb_sync = atyfb_sync;
		info->flags &= ~FBINFO_HWACCEL_DISABLED;
	} else {
		info->fbops->fb_sync = NULL;
		info->flags |= FBINFO_HWACCEL_DISABLED;
	}

	if (par->blitter_may_be_busy)
		wait_for_idle(par);

	aty_set_crtc(par, &par->crtc);
	par->dac_ops->set_dac(info, &par->pll,
			      var->bits_per_pixel, par->accel_flags);
	par->pll_ops->set_pll(info, &par->pll);

#ifdef DEBUG
	if (par->pll_ops && par->pll_ops->pll_to_var)
		pixclock_in_ps = par->pll_ops->pll_to_var(info, &par->pll);
	else
		pixclock_in_ps = 0;

	if (0 == pixclock_in_ps) {
		PRINTKE("ALERT ops->pll_to_var get 0\n");
		pixclock_in_ps = pixclock;
	}

	memset(&debug, 0, sizeof(debug));
	if (!aty_crtc_to_var(&par->crtc, &debug)) {
		u32 hSync, vRefresh;
		u32 h_disp, h_sync_strt, h_sync_end, h_total;
		u32 v_disp, v_sync_strt, v_sync_end, v_total;

		h_disp = debug.xres;
		h_sync_strt = h_disp + debug.right_margin;
		h_sync_end = h_sync_strt + debug.hsync_len;
		h_total = h_sync_end + debug.left_margin;
		v_disp = debug.yres;
		v_sync_strt = v_disp + debug.lower_margin;
		v_sync_end = v_sync_strt + debug.vsync_len;
		v_total = v_sync_end + debug.upper_margin;

		hSync = 1000000000 / (pixclock_in_ps * h_total);
		vRefresh = (hSync * 1000) / v_total;
		if (par->crtc.gen_cntl & CRTC_INTERLACE_EN)
			vRefresh *= 2;
		if (par->crtc.gen_cntl & CRTC_DBL_SCAN_EN)
			vRefresh /= 2;

		DPRINTK("atyfb_set_par\n");
		DPRINTK(" Set Visible Mode to %ix%i-%i\n",
			var->xres, var->yres, var->bits_per_pixel);
		DPRINTK(" Virtual resolution %ix%i, "
			"pixclock_in_ps %i (calculated %i)\n",
			var->xres_virtual, var->yres_virtual,
			pixclock, pixclock_in_ps);
		DPRINTK(" Dot clock:           %i MHz\n",
			1000000 / pixclock_in_ps);
		DPRINTK(" Horizontal sync:     %i kHz\n", hSync);
		DPRINTK(" Vertical refresh:    %i Hz\n", vRefresh);
		DPRINTK(" x  style: %i.%03i %i %i %i %i   %i %i %i %i\n",
			1000000 / pixclock_in_ps, 1000000 % pixclock_in_ps,
			h_disp, h_sync_strt, h_sync_end, h_total,
			v_disp, v_sync_strt, v_sync_end, v_total);
		DPRINTK(" fb style: %i  %i %i %i %i %i %i %i %i\n",
			pixclock_in_ps,
			debug.left_margin, h_disp, debug.right_margin, debug.hsync_len,
			debug.upper_margin, v_disp, debug.lower_margin, debug.vsync_len);
	}
#endif /* DEBUG */

	if (!M64_HAS(INTEGRATED)) {
		/* Don't forget MEM_CNTL */
		tmp = aty_ld_le32(MEM_CNTL, par) & 0xf0ffffff;
		switch (var->bits_per_pixel) {
		case 8:
			tmp |= 0x02000000;
			break;
		case 16:
			tmp |= 0x03000000;
			break;
		case 32:
			tmp |= 0x06000000;
			break;
		}
		aty_st_le32(MEM_CNTL, tmp, par);
	} else {
		tmp = aty_ld_le32(MEM_CNTL, par) & 0xf00fffff;
		if (!M64_HAS(MAGIC_POSTDIV))
			tmp |= par->mem_refresh_rate << 20;
		switch (var->bits_per_pixel) {
		case 8:
		case 24:
			tmp |= 0x00000000;
			break;
		case 16:
			tmp |= 0x04000000;
			break;
		case 32:
			tmp |= 0x08000000;
			break;
		}
		if (M64_HAS(CT_BUS)) {
			aty_st_le32(DAC_CNTL, 0x87010184, par);
			aty_st_le32(BUS_CNTL, 0x680000f9, par);
		} else if (M64_HAS(VT_BUS)) {
			aty_st_le32(DAC_CNTL, 0x87010184, par);
			aty_st_le32(BUS_CNTL, 0x680000f9, par);
		} else if (M64_HAS(MOBIL_BUS)) {
			aty_st_le32(DAC_CNTL, 0x80010102, par);
			aty_st_le32(BUS_CNTL, 0x7b33a040 | (par->aux_start ? BUS_APER_REG_DIS : 0), par);
		} else {
			/* GT */
			aty_st_le32(DAC_CNTL, 0x86010102, par);
			aty_st_le32(BUS_CNTL, 0x7b23a040 | (par->aux_start ? BUS_APER_REG_DIS : 0), par);
			aty_st_le32(EXT_MEM_CNTL, aty_ld_le32(EXT_MEM_CNTL, par) | 0x5000001, par);
		}
		aty_st_le32(MEM_CNTL, tmp, par);
	}
	aty_st_8(DAC_MASK, 0xff, par);

	info->fix.line_length = calc_line_length(par, var->xres_virtual,
						 var->bits_per_pixel);

	info->fix.visual = var->bits_per_pixel <= 8 ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_DIRECTCOLOR;

	/* Initialize the graphics engine */
	if (par->accel_flags & FB_ACCELF_TEXT)
		aty_init_engine(par, info);

#ifdef CONFIG_BOOTX_TEXT
	btext_update_display(info->fix.smem_start,
		(((par->crtc.h_tot_disp >> 16) & 0xff) + 1) * 8,
		((par->crtc.v_tot_disp >> 16) & 0x7ff) + 1,
		var->bits_per_pixel,
		par->crtc.vxres * var->bits_per_pixel / 8);
#endif /* CONFIG_BOOTX_TEXT */
#ifdef DEBUG
{
	/* dump non shadow CRTC, pll, LCD registers */
	int i; u32 base;

	/* CRTC registers */
	base = 0x2000;
	printk("debug atyfb: Mach64 non-shadow register values:");
	for (i = 0; i < 256; i = i+4) {
		if (i % 16 == 0) {
			pr_cont("\n");
			printk("debug atyfb: 0x%04X: ", base + i);
		}
		pr_cont(" %08X", aty_ld_le32(i, par));
	}
	pr_cont("\n\n");

#ifdef CONFIG_FB_ATY_CT
	/* PLL registers */
	base = 0x00;
	printk("debug atyfb: Mach64 PLL register values:");
	for (i = 0; i < 64; i++) {
		if (i % 16 == 0) {
			pr_cont("\n");
			printk("debug atyfb: 0x%02X: ", base + i);
		}
		if (i % 4 == 0)
			pr_cont(" ");
		pr_cont("%02X", aty_ld_pll_ct(i, par));
	}
	pr_cont("\n\n");
#endif	/* CONFIG_FB_ATY_CT */

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		/* LCD registers */
		base = 0x00;
		printk("debug atyfb: LCD register values:");
		if (M64_HAS(LT_LCD_REGS)) {
			for (i = 0; i <= POWER_MANAGEMENT; i++) {
				if (i == EXT_VERT_STRETCH)
					continue;
				pr_cont("\ndebug atyfb: 0x%04X: ",
				       lt_lcd_regs[i]);
				pr_cont(" %08X", aty_ld_lcd(i, par));
			}
		} else {
			for (i = 0; i < 64; i++) {
				if (i % 4 == 0)
					pr_cont("\ndebug atyfb: 0x%02X: ",
					       base + i);
				pr_cont(" %08X", aty_ld_lcd(i, par));
			}
		}
		pr_cont("\n\n");
	}
#endif /* CONFIG_FB_ATY_GENERIC_LCD */
}
#endif /* DEBUG */
	return 0;
}