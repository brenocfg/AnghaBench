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
struct i740fb_par {int video_clk2_m; int video_clk2_n; int video_clk2_mn_msbs; int video_clk2_div_sel; int pixelpipe_cfg0; int misc; int* seq; int* crtc; int* gdc; int* atc; int ext_vert_total; int ext_vert_disp_end; int ext_vert_sync_start; int ext_vert_blank_start; int ext_horiz_total; int ext_horiz_blank; int ext_offset; int ext_start_addr_hi; int ext_start_addr; int interlace_cntl; int address_mapping; int bitblt_cntl; int display_cntl; int pixelpipe_cfg2; int pll_cntl; int pixelpipe_cfg1; int lmi_fifo_watermark; int io_cntl; scalar_t__ regs; } ;
struct TYPE_3__ {int line_length; int /*<<< orphan*/  visual; } ;
struct TYPE_4__ {int xres_virtual; int bits_per_pixel; } ;
struct fb_info {TYPE_1__ fix; TYPE_2__ var; int /*<<< orphan*/  screen_size; int /*<<< orphan*/  screen_base; struct i740fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_MAPPING ; 
 int /*<<< orphan*/  BITBLT_CNTL ; 
 int BLANK_DISP_OVERLAY ; 
 int COLEXP_MODE ; 
 int /*<<< orphan*/  COL_KEY_CNTL_1 ; 
 int DAC_8_BIT ; 
 int DISPLAY_8BPP_MODE ; 
 int /*<<< orphan*/  DISPLAY_CNTL ; 
 int DISPLAY_COLOR_MODE ; 
 int DRAM_EXT_CNTL ; 
 int DRAM_REFRESH_60HZ ; 
 int DRAM_REFRESH_DISABLE ; 
 int EXTENDED_ATTR_CNTL ; 
 int EXTENDED_CRTC_CNTL ; 
 int EXT_HORIZ_BLANK ; 
 int EXT_HORIZ_TOTAL ; 
 int EXT_OFFSET ; 
 int EXT_START_ADDR ; 
 int EXT_START_ADDR_HI ; 
 int EXT_VERT_BLANK_START ; 
 int EXT_VERT_DISPLAY ; 
 int EXT_VERT_SYNC_START ; 
 int EXT_VERT_TOTAL ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 scalar_t__ FWATER_BLC ; 
 int GUI_MODE ; 
 int /*<<< orphan*/  INTERLACE_CNTL ; 
 int INTERLACE_ENABLE ; 
 int /*<<< orphan*/  IO_CTNL ; 
 int LMI_BURST_LENGTH ; 
 int LMI_FIFO_WATERMARK ; 
 int /*<<< orphan*/  MRX ; 
 int /*<<< orphan*/  PIXPIPE_CONFIG_0 ; 
 int /*<<< orphan*/  PIXPIPE_CONFIG_1 ; 
 int /*<<< orphan*/  PIXPIPE_CONFIG_2 ; 
 int PLL_CNTL ; 
 int VCLK2_VCO_DIV_SEL ; 
 int VCLK2_VCO_M ; 
 int VCLK2_VCO_MN_MSBS ; 
 int VCLK2_VCO_N ; 
 int VGA_ATT_C ; 
 int VGA_ATT_IW ; 
 size_t VGA_CRTC_V_SYNC_END ; 
 int VGA_CRT_C ; 
 int /*<<< orphan*/  VGA_CRT_IC ; 
 int VGA_GFX_C ; 
 int /*<<< orphan*/  VGA_GFX_I ; 
 int VGA_IS1_RC ; 
 int VGA_MIS_W ; 
 int VGA_PEL_D ; 
 int VGA_PEL_IW ; 
 int VGA_PEL_MSK ; 
 int VGA_SEQ_C ; 
 size_t VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 int VGA_SEQ_RESET ; 
 int VGA_WRAP_MODE ; 
 int /*<<< orphan*/  XRX ; 
 int i740fb_decode_var (TYPE_2__*,struct i740fb_par*,struct fb_info*) ; 
 int /*<<< orphan*/  i740inb (struct i740fb_par*,int) ; 
 int /*<<< orphan*/  i740outb (struct i740fb_par*,int,int) ; 
 int /*<<< orphan*/  i740outreg (struct i740fb_par*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i740outreg_mask (struct i740fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  vga_protect (struct i740fb_par*) ; 
 int /*<<< orphan*/  vga_unprotect (struct i740fb_par*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i740fb_set_par(struct fb_info *info)
{
	struct i740fb_par *par = info->par;
	u32 itemp;
	int i;

	i = i740fb_decode_var(&info->var, par, info);
	if (i)
		return i;

	memset(info->screen_base, 0, info->screen_size);

	vga_protect(par);

	i740outreg(par, XRX, DRAM_EXT_CNTL, DRAM_REFRESH_DISABLE);

	mdelay(1);

	i740outreg(par, XRX, VCLK2_VCO_M, par->video_clk2_m);
	i740outreg(par, XRX, VCLK2_VCO_N, par->video_clk2_n);
	i740outreg(par, XRX, VCLK2_VCO_MN_MSBS, par->video_clk2_mn_msbs);
	i740outreg(par, XRX, VCLK2_VCO_DIV_SEL, par->video_clk2_div_sel);

	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_0,
			par->pixelpipe_cfg0 & DAC_8_BIT, 0x80);

	i740inb(par, 0x3DA);
	i740outb(par, 0x3C0, 0x00);

	/* update misc output register */
	i740outb(par, VGA_MIS_W, par->misc | 0x01);

	/* synchronous reset on */
	i740outreg(par, VGA_SEQ_I, VGA_SEQ_RESET, 0x01);
	/* write sequencer registers */
	i740outreg(par, VGA_SEQ_I, VGA_SEQ_CLOCK_MODE,
			par->seq[VGA_SEQ_CLOCK_MODE] | 0x20);
	for (i = 2; i < VGA_SEQ_C; i++)
		i740outreg(par, VGA_SEQ_I, i, par->seq[i]);

	/* synchronous reset off */
	i740outreg(par, VGA_SEQ_I, VGA_SEQ_RESET, 0x03);

	/* deprotect CRT registers 0-7 */
	i740outreg(par, VGA_CRT_IC, VGA_CRTC_V_SYNC_END,
			par->crtc[VGA_CRTC_V_SYNC_END]);

	/* write CRT registers */
	for (i = 0; i < VGA_CRT_C; i++)
		i740outreg(par, VGA_CRT_IC, i, par->crtc[i]);

	/* write graphics controller registers */
	for (i = 0; i < VGA_GFX_C; i++)
		i740outreg(par, VGA_GFX_I, i, par->gdc[i]);

	/* write attribute controller registers */
	for (i = 0; i < VGA_ATT_C; i++) {
		i740inb(par, VGA_IS1_RC);		/* reset flip-flop */
		i740outb(par, VGA_ATT_IW, i);
		i740outb(par, VGA_ATT_IW, par->atc[i]);
	}

	i740inb(par, VGA_IS1_RC);
	i740outb(par, VGA_ATT_IW, 0x20);

	i740outreg(par, VGA_CRT_IC, EXT_VERT_TOTAL, par->ext_vert_total);
	i740outreg(par, VGA_CRT_IC, EXT_VERT_DISPLAY, par->ext_vert_disp_end);
	i740outreg(par, VGA_CRT_IC, EXT_VERT_SYNC_START,
			par->ext_vert_sync_start);
	i740outreg(par, VGA_CRT_IC, EXT_VERT_BLANK_START,
			par->ext_vert_blank_start);
	i740outreg(par, VGA_CRT_IC, EXT_HORIZ_TOTAL, par->ext_horiz_total);
	i740outreg(par, VGA_CRT_IC, EXT_HORIZ_BLANK, par->ext_horiz_blank);
	i740outreg(par, VGA_CRT_IC, EXT_OFFSET, par->ext_offset);
	i740outreg(par, VGA_CRT_IC, EXT_START_ADDR_HI, par->ext_start_addr_hi);
	i740outreg(par, VGA_CRT_IC, EXT_START_ADDR, par->ext_start_addr);

	i740outreg_mask(par, VGA_CRT_IC, INTERLACE_CNTL,
			par->interlace_cntl, INTERLACE_ENABLE);
	i740outreg_mask(par, XRX, ADDRESS_MAPPING, par->address_mapping, 0x1F);
	i740outreg_mask(par, XRX, BITBLT_CNTL, par->bitblt_cntl, COLEXP_MODE);
	i740outreg_mask(par, XRX, DISPLAY_CNTL,
			par->display_cntl, VGA_WRAP_MODE | GUI_MODE);
	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_0, par->pixelpipe_cfg0, 0x9B);
	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_2, par->pixelpipe_cfg2, 0x0C);

	i740outreg(par, XRX, PLL_CNTL, par->pll_cntl);

	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_1,
			par->pixelpipe_cfg1, DISPLAY_COLOR_MODE);

	itemp = readl(par->regs + FWATER_BLC);
	itemp &= ~(LMI_BURST_LENGTH | LMI_FIFO_WATERMARK);
	itemp |= par->lmi_fifo_watermark;
	writel(itemp, par->regs + FWATER_BLC);

	i740outreg(par, XRX, DRAM_EXT_CNTL, DRAM_REFRESH_60HZ);

	i740outreg_mask(par, MRX, COL_KEY_CNTL_1, 0, BLANK_DISP_OVERLAY);
	i740outreg_mask(par, XRX, IO_CTNL,
			par->io_cntl, EXTENDED_ATTR_CNTL | EXTENDED_CRTC_CNTL);

	if (par->pixelpipe_cfg1 != DISPLAY_8BPP_MODE) {
		i740outb(par, VGA_PEL_MSK, 0xFF);
		i740outb(par, VGA_PEL_IW, 0x00);
		for (i = 0; i < 256; i++) {
			itemp = (par->pixelpipe_cfg0 & DAC_8_BIT) ? i : i >> 2;
			i740outb(par, VGA_PEL_D, itemp);
			i740outb(par, VGA_PEL_D, itemp);
			i740outb(par, VGA_PEL_D, itemp);
		}
	}

	/* Wait for screen to stabilize. */
	mdelay(50);
	vga_unprotect(par);

	info->fix.line_length =
			info->var.xres_virtual * info->var.bits_per_pixel / 8;
	if (info->var.bits_per_pixel == 8)
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	else
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	return 0;
}