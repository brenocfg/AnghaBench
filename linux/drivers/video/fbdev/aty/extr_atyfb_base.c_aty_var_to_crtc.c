#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int length; } ;
struct fb_var_screeninfo {int xres; int yres; int xres_virtual; int yres_virtual; int xoffset; int yoffset; int bits_per_pixel; int sync; int vmode; int right_margin; int hsync_len; int left_margin; int lower_margin; int vsync_len; int upper_margin; int activate; TYPE_1__ green; } ;
struct TYPE_4__ {int smem_len; } ;
struct fb_info {TYPE_2__ fix; scalar_t__ par; } ;
struct crtc {int lcd_index; int lcd_config_panel; int lcd_gen_cntl; int vxres; int vyres; int xoffset; int yoffset; int bpp; int off_pitch; int h_tot_disp; int h_sync_strt_wid; int v_tot_disp; int v_sync_strt_wid; int gen_cntl; int horz_stretching; int ext_vert_stretch; int vert_stretching; int shadow_h_tot_disp; int shadow_h_sync_strt_wid; int shadow_v_tot_disp; int shadow_v_sync_strt_wid; int dp_pix_width; int dp_chain_mask; scalar_t__ vline_crnt_vline; } ;
struct atyfb_par {scalar_t__ lcd_table; int lcd_width; int lcd_height; int lcd_right_margin; int lcd_hsync_len; int lcd_hsync_dly; int lcd_hblank_len; int lcd_lower_margin; int lcd_vsync_len; int lcd_vblank_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIReduceRatio (int*,int*) ; 
 int AUTO_HORZ_RATIO ; 
 int AUTO_VERT_RATIO ; 
 int BYTE_ORDER_LSB_TO_MSB ; 
 int /*<<< orphan*/  CNFG_PANEL ; 
 int CRTC2_DISPLAY_DIS ; 
 int CRTC2_EN ; 
 int CRTC2_PIX_WIDTH ; 
 int CRTC_CSYNC_EN ; 
 int CRTC_DBL_SCAN_EN ; 
 int CRTC_EN ; 
 int CRTC_EXT_DISP_EN ; 
 int CRTC_FIFO_LWM ; 
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
 int CRTC_INTERLACE_EN ; 
 int CRTC_PIX_WIDTH_15BPP ; 
 int CRTC_PIX_WIDTH_16BPP ; 
 int CRTC_PIX_WIDTH_24BPP ; 
 int CRTC_PIX_WIDTH_32BPP ; 
 int CRTC_PIX_WIDTH_8BPP ; 
 int CRTC_RW_SELECT ; 
 int CRTC_VGA_LINEAR ; 
 int CRT_ON ; 
 int DIS_HOR_CRT_DIVBY2 ; 
 int DONT_SHADOW_VPAR ; 
 int DP_CHAIN_15BPP ; 
 int DP_CHAIN_16BPP ; 
 int DP_CHAIN_24BPP ; 
 int DP_CHAIN_32BPP ; 
 int DP_CHAIN_8BPP ; 
 int DST_15BPP ; 
 int DST_16BPP ; 
 int DST_32BPP ; 
 int DST_8BPP ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXT_VERT_STRETCH ; 
 int /*<<< orphan*/  FAIL (char*) ; 
 int /*<<< orphan*/  FAIL_MAX (char*,int,int) ; 
 int FB_ACTIVATE_TEST ; 
 int FB_SYNC_COMP_HIGH_ACT ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int HORZ_DIVBY2_EN ; 
 int /*<<< orphan*/  HORZ_STRETCHING ; 
 int HORZ_STRETCH_BLEND ; 
 int HORZ_STRETCH_EN ; 
 int HORZ_STRETCH_LOOP ; 
 int HORZ_STRETCH_MODE ; 
 int HORZ_STRETCH_RATIO ; 
 int HOST_15BPP ; 
 int HOST_16BPP ; 
 int HOST_32BPP ; 
 int HOST_8BPP ; 
 int /*<<< orphan*/  INTEGRATED ; 
 int LCD_DISPLAY_DIS ; 
 int /*<<< orphan*/  LCD_GEN_CNTL ; 
 int /*<<< orphan*/  LCD_INDEX ; 
 int LCD_INDEX_MASK ; 
 int LCD_ON ; 
 int LCD_SRC_SEL ; 
 int LOCK_8DOT ; 
 int /*<<< orphan*/  LT_LCD_REGS ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_FIFO ; 
 int /*<<< orphan*/  MOBIL_BUS ; 
 int /*<<< orphan*/  PRINTKE (char*) ; 
 int /*<<< orphan*/  PRINTKI (char*) ; 
 int SHADOW_EN ; 
 int SHADOW_RW_EN ; 
 int SRC_15BPP ; 
 int SRC_16BPP ; 
 int SRC_32BPP ; 
 int SRC_8BPP ; 
 int TVCLK_PM_EN ; 
 int USE_SHADOWED_ROWCUR ; 
 int USE_SHADOWED_VEND ; 
 int VERT_STRETCH_EN ; 
 int VERT_STRETCH_MODE ; 
 int VERT_STRETCH_RATIO0 ; 
 int VERT_STRETCH_RATIO3 ; 
 int VERT_STRETCH_USE0 ; 
 int aty_ld_lcd (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int calc_line_length (struct atyfb_par*,int,int) ; 

__attribute__((used)) static int aty_var_to_crtc(const struct fb_info *info,
			   const struct fb_var_screeninfo *var,
			   struct crtc *crtc)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 xres, yres, vxres, vyres, xoffset, yoffset, bpp;
	u32 sync, vmode;
	u32 h_total, h_disp, h_sync_strt, h_sync_end, h_sync_dly, h_sync_wid, h_sync_pol;
	u32 v_total, v_disp, v_sync_strt, v_sync_end, v_sync_wid, v_sync_pol, c_sync;
	u32 pix_width, dp_pix_width, dp_chain_mask;
	u32 line_length;

	/* input */
	xres = (var->xres + 7) & ~7;
	yres = var->yres;
	vxres = (var->xres_virtual + 7) & ~7;
	vyres = var->yres_virtual;
	xoffset = (var->xoffset + 7) & ~7;
	yoffset = var->yoffset;
	bpp = var->bits_per_pixel;
	if (bpp == 16)
		bpp = (var->green.length == 5) ? 15 : 16;
	sync = var->sync;
	vmode = var->vmode;

	/* convert (and round up) and validate */
	if (vxres < xres + xoffset)
		vxres = xres + xoffset;
	h_disp = xres;

	if (vyres < yres + yoffset)
		vyres = yres + yoffset;
	v_disp = yres;

	if (bpp <= 8) {
		bpp = 8;
		pix_width = CRTC_PIX_WIDTH_8BPP;
		dp_pix_width = HOST_8BPP | SRC_8BPP | DST_8BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_8BPP;
	} else if (bpp <= 15) {
		bpp = 16;
		pix_width = CRTC_PIX_WIDTH_15BPP;
		dp_pix_width = HOST_15BPP | SRC_15BPP | DST_15BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_15BPP;
	} else if (bpp <= 16) {
		bpp = 16;
		pix_width = CRTC_PIX_WIDTH_16BPP;
		dp_pix_width = HOST_16BPP | SRC_16BPP | DST_16BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_16BPP;
	} else if (bpp <= 24 && M64_HAS(INTEGRATED)) {
		bpp = 24;
		pix_width = CRTC_PIX_WIDTH_24BPP;
		dp_pix_width = HOST_8BPP | SRC_8BPP | DST_8BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_24BPP;
	} else if (bpp <= 32) {
		bpp = 32;
		pix_width = CRTC_PIX_WIDTH_32BPP;
		dp_pix_width = HOST_32BPP | SRC_32BPP | DST_32BPP |
			BYTE_ORDER_LSB_TO_MSB;
		dp_chain_mask = DP_CHAIN_32BPP;
	} else
		FAIL("invalid bpp");

	line_length = calc_line_length(par, vxres, bpp);

	if (vyres * line_length > info->fix.smem_len)
		FAIL("not enough video RAM");

	h_sync_pol = sync & FB_SYNC_HOR_HIGH_ACT ? 0 : 1;
	v_sync_pol = sync & FB_SYNC_VERT_HIGH_ACT ? 0 : 1;

	if ((xres > 1920) || (yres > 1200)) {
		FAIL("MACH64 chips are designed for max 1920x1200\n"
		     "select another resolution.");
	}
	h_sync_strt = h_disp + var->right_margin;
	h_sync_end = h_sync_strt + var->hsync_len;
	h_sync_dly  = var->right_margin & 7;
	h_total = h_sync_end + h_sync_dly + var->left_margin;

	v_sync_strt = v_disp + var->lower_margin;
	v_sync_end = v_sync_strt + var->vsync_len;
	v_total = v_sync_end + var->upper_margin;

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		if (!M64_HAS(LT_LCD_REGS)) {
			u32 lcd_index = aty_ld_le32(LCD_INDEX, par);
			crtc->lcd_index = lcd_index &
				~(LCD_INDEX_MASK | LCD_DISPLAY_DIS |
				  LCD_SRC_SEL | CRTC2_DISPLAY_DIS);
			aty_st_le32(LCD_INDEX, lcd_index, par);
		}

		if (!M64_HAS(MOBIL_BUS))
			crtc->lcd_index |= CRTC2_DISPLAY_DIS;

		crtc->lcd_config_panel = aty_ld_lcd(CNFG_PANEL, par) | 0x4000;
		crtc->lcd_gen_cntl = aty_ld_lcd(LCD_GEN_CNTL, par) & ~CRTC_RW_SELECT;

		crtc->lcd_gen_cntl &=
			~(HORZ_DIVBY2_EN | DIS_HOR_CRT_DIVBY2 | TVCLK_PM_EN |
			/*VCLK_DAC_PM_EN | USE_SHADOWED_VEND |*/
			USE_SHADOWED_ROWCUR | SHADOW_EN | SHADOW_RW_EN);
		crtc->lcd_gen_cntl |= DONT_SHADOW_VPAR | LOCK_8DOT;

		if ((crtc->lcd_gen_cntl & LCD_ON) &&
		    ((xres > par->lcd_width) || (yres > par->lcd_height))) {
			/*
			 * We cannot display the mode on the LCD. If the CRT is
			 * enabled we can turn off the LCD.
			 * If the CRT is off, it isn't a good idea to switch it
			 * on; we don't know if one is connected. So it's better
			 * to fail then.
			 */
			if (crtc->lcd_gen_cntl & CRT_ON) {
				if (!(var->activate & FB_ACTIVATE_TEST))
					PRINTKI("Disable LCD panel, because video mode does not fit.\n");
				crtc->lcd_gen_cntl &= ~LCD_ON;
				/*aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl, par);*/
			} else {
				if (!(var->activate & FB_ACTIVATE_TEST))
					PRINTKE("Video mode exceeds size of LCD panel.\nConnect this computer to a conventional monitor if you really need this mode.\n");
				return -EINVAL;
			}
		}
	}

	if ((par->lcd_table != 0) && (crtc->lcd_gen_cntl & LCD_ON)) {
		int VScan = 1;
		/* bpp -> bytespp, 1,4 -> 0; 8 -> 2; 15,16 -> 1; 24 -> 6; 32 -> 5
		const u8 DFP_h_sync_dly_LT[] = { 0, 2, 1, 6, 5 };
		const u8 ADD_to_strt_wid_and_dly_LT_DAC[] = { 0, 5, 6, 9, 9, 12, 12 };  */

		vmode &= ~(FB_VMODE_DOUBLE | FB_VMODE_INTERLACED);

		/*
		 * This is horror! When we simulate, say 640x480 on an 800x600
		 * LCD monitor, the CRTC should be programmed 800x600 values for
		 * the non visible part, but 640x480 for the visible part.
		 * This code has been tested on a laptop with it's 1400x1050 LCD
		 * monitor and a conventional monitor both switched on.
		 * Tested modes: 1280x1024, 1152x864, 1024x768, 800x600,
		 * works with little glitches also with DOUBLESCAN modes
		 */
		if (yres < par->lcd_height) {
			VScan = par->lcd_height / yres;
			if (VScan > 1) {
				VScan = 2;
				vmode |= FB_VMODE_DOUBLE;
			}
		}

		h_sync_strt = h_disp + par->lcd_right_margin;
		h_sync_end = h_sync_strt + par->lcd_hsync_len;
		h_sync_dly = /*DFP_h_sync_dly[ ( bpp + 1 ) / 3 ]; */par->lcd_hsync_dly;
		h_total = h_disp + par->lcd_hblank_len;

		v_sync_strt = v_disp + par->lcd_lower_margin / VScan;
		v_sync_end = v_sync_strt + par->lcd_vsync_len / VScan;
		v_total = v_disp + par->lcd_vblank_len / VScan;
	}
#endif /* CONFIG_FB_ATY_GENERIC_LCD */

	h_disp = (h_disp >> 3) - 1;
	h_sync_strt = (h_sync_strt >> 3) - 1;
	h_sync_end = (h_sync_end >> 3) - 1;
	h_total = (h_total >> 3) - 1;
	h_sync_wid = h_sync_end - h_sync_strt;

	FAIL_MAX("h_disp too large", h_disp, 0xff);
	FAIL_MAX("h_sync_strt too large", h_sync_strt, 0x1ff);
	/*FAIL_MAX("h_sync_wid too large", h_sync_wid, 0x1f);*/
	if (h_sync_wid > 0x1f)
		h_sync_wid = 0x1f;
	FAIL_MAX("h_total too large", h_total, 0x1ff);

	if (vmode & FB_VMODE_DOUBLE) {
		v_disp <<= 1;
		v_sync_strt <<= 1;
		v_sync_end <<= 1;
		v_total <<= 1;
	}

	v_disp--;
	v_sync_strt--;
	v_sync_end--;
	v_total--;
	v_sync_wid = v_sync_end - v_sync_strt;

	FAIL_MAX("v_disp too large", v_disp, 0x7ff);
	FAIL_MAX("v_sync_stsrt too large", v_sync_strt, 0x7ff);
	/*FAIL_MAX("v_sync_wid too large", v_sync_wid, 0x1f);*/
	if (v_sync_wid > 0x1f)
		v_sync_wid = 0x1f;
	FAIL_MAX("v_total too large", v_total, 0x7ff);

	c_sync = sync & FB_SYNC_COMP_HIGH_ACT ? CRTC_CSYNC_EN : 0;

	/* output */
	crtc->vxres = vxres;
	crtc->vyres = vyres;
	crtc->xoffset = xoffset;
	crtc->yoffset = yoffset;
	crtc->bpp = bpp;
	crtc->off_pitch =
		((yoffset * line_length + xoffset * bpp / 8) / 8) |
		((line_length / bpp) << 22);
	crtc->vline_crnt_vline = 0;

	crtc->h_tot_disp = h_total | (h_disp << 16);
	crtc->h_sync_strt_wid = (h_sync_strt & 0xff) | (h_sync_dly << 8) |
		((h_sync_strt & 0x100) << 4) | (h_sync_wid << 16) |
		(h_sync_pol << 21);
	crtc->v_tot_disp = v_total | (v_disp << 16);
	crtc->v_sync_strt_wid = v_sync_strt | (v_sync_wid << 16) |
		(v_sync_pol << 21);

	/* crtc->gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par) & CRTC_PRESERVED_MASK; */
	crtc->gen_cntl = CRTC_EXT_DISP_EN | CRTC_EN | pix_width | c_sync;
	crtc->gen_cntl |= CRTC_VGA_LINEAR;

	/* Enable doublescan mode if requested */
	if (vmode & FB_VMODE_DOUBLE)
		crtc->gen_cntl |= CRTC_DBL_SCAN_EN;
	/* Enable interlaced mode if requested */
	if (vmode & FB_VMODE_INTERLACED)
		crtc->gen_cntl |= CRTC_INTERLACE_EN;
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		u32 vdisplay = yres;
		if (vmode & FB_VMODE_DOUBLE)
			vdisplay <<= 1;
		crtc->gen_cntl &= ~(CRTC2_EN | CRTC2_PIX_WIDTH);
		crtc->lcd_gen_cntl &= ~(HORZ_DIVBY2_EN | DIS_HOR_CRT_DIVBY2 |
					/*TVCLK_PM_EN | VCLK_DAC_PM_EN |*/
					USE_SHADOWED_VEND |
					USE_SHADOWED_ROWCUR |
					SHADOW_EN | SHADOW_RW_EN);
		crtc->lcd_gen_cntl |= DONT_SHADOW_VPAR/* | LOCK_8DOT*/;

		/* MOBILITY M1 tested, FIXME: LT */
		crtc->horz_stretching = aty_ld_lcd(HORZ_STRETCHING, par);
		if (!M64_HAS(LT_LCD_REGS))
			crtc->ext_vert_stretch = aty_ld_lcd(EXT_VERT_STRETCH, par) &
				~(AUTO_VERT_RATIO | VERT_STRETCH_MODE | VERT_STRETCH_RATIO3);

		crtc->horz_stretching &= ~(HORZ_STRETCH_RATIO |
					   HORZ_STRETCH_LOOP | AUTO_HORZ_RATIO |
					   HORZ_STRETCH_MODE | HORZ_STRETCH_EN);
		if (xres < par->lcd_width && crtc->lcd_gen_cntl & LCD_ON) {
			do {
				/*
				 * The horizontal blender misbehaves when
				 * HDisplay is less than a certain threshold
				 * (440 for a 1024-wide panel).  It doesn't
				 * stretch such modes enough.  Use pixel
				 * replication instead of blending to stretch
				 * modes that can be made to exactly fit the
				 * panel width.  The undocumented "NoLCDBlend"
				 * option allows the pixel-replicated mode to
				 * be slightly wider or narrower than the
				 * panel width.  It also causes a mode that is
				 * exactly half as wide as the panel to be
				 * pixel-replicated, rather than blended.
				 */
				int HDisplay  = xres & ~7;
				int nStretch  = par->lcd_width / HDisplay;
				int Remainder = par->lcd_width % HDisplay;

				if ((!Remainder && ((nStretch > 2))) ||
				    (((HDisplay * 16) / par->lcd_width) < 7)) {
					static const char StretchLoops[] = { 10, 12, 13, 15, 16 };
					int horz_stretch_loop = -1, BestRemainder;
					int Numerator = HDisplay, Denominator = par->lcd_width;
					int Index = 5;
					ATIReduceRatio(&Numerator, &Denominator);

					BestRemainder = (Numerator * 16) / Denominator;
					while (--Index >= 0) {
						Remainder = ((Denominator - Numerator) * StretchLoops[Index]) %
							Denominator;
						if (Remainder < BestRemainder) {
							horz_stretch_loop = Index;
							if (!(BestRemainder = Remainder))
								break;
						}
					}

					if ((horz_stretch_loop >= 0) && !BestRemainder) {
						int horz_stretch_ratio = 0, Accumulator = 0;
						int reuse_previous = 1;

						Index = StretchLoops[horz_stretch_loop];

						while (--Index >= 0) {
							if (Accumulator > 0)
								horz_stretch_ratio |= reuse_previous;
							else
								Accumulator += Denominator;
							Accumulator -= Numerator;
							reuse_previous <<= 1;
						}

						crtc->horz_stretching |= (HORZ_STRETCH_EN |
							((horz_stretch_loop & HORZ_STRETCH_LOOP) << 16) |
							(horz_stretch_ratio & HORZ_STRETCH_RATIO));
						break;      /* Out of the do { ... } while (0) */
					}
				}

				crtc->horz_stretching |= (HORZ_STRETCH_MODE | HORZ_STRETCH_EN |
					(((HDisplay * (HORZ_STRETCH_BLEND + 1)) / par->lcd_width) & HORZ_STRETCH_BLEND));
			} while (0);
		}

		if (vdisplay < par->lcd_height && crtc->lcd_gen_cntl & LCD_ON) {
			crtc->vert_stretching = (VERT_STRETCH_USE0 | VERT_STRETCH_EN |
				(((vdisplay * (VERT_STRETCH_RATIO0 + 1)) / par->lcd_height) & VERT_STRETCH_RATIO0));

			if (!M64_HAS(LT_LCD_REGS) &&
			    xres <= (M64_HAS(MOBIL_BUS) ? 1024 : 800))
				crtc->ext_vert_stretch |= VERT_STRETCH_MODE;
		} else {
			/*
			 * Don't use vertical blending if the mode is too wide
			 * or not vertically stretched.
			 */
			crtc->vert_stretching = 0;
		}
		/* copy to shadow crtc */
		crtc->shadow_h_tot_disp = crtc->h_tot_disp;
		crtc->shadow_h_sync_strt_wid = crtc->h_sync_strt_wid;
		crtc->shadow_v_tot_disp = crtc->v_tot_disp;
		crtc->shadow_v_sync_strt_wid = crtc->v_sync_strt_wid;
	}
#endif /* CONFIG_FB_ATY_GENERIC_LCD */

	if (M64_HAS(MAGIC_FIFO)) {
		/* FIXME: display FIFO low watermark values */
		crtc->gen_cntl |= (aty_ld_le32(CRTC_GEN_CNTL, par) & CRTC_FIFO_LWM);
	}
	crtc->dp_pix_width = dp_pix_width;
	crtc->dp_chain_mask = dp_chain_mask;

	return 0;
}