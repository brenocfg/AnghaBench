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
struct fb_info {scalar_t__ screen_size; int /*<<< orphan*/  device; struct cirrusfb_info* par; } ;
struct cirrusfb_info {size_t btype; int /*<<< orphan*/  regbase; } ;
struct cirrusfb_board_info_rec {int sr07; scalar_t__ init_sr07; } ;

/* Variables and functions */
#define  BT_ALPINE 136 
#define  BT_GD5480 135 
#define  BT_LAGUNA 134 
#define  BT_LAGUNAB 133 
#define  BT_PICASSO 132 
#define  BT_PICASSO4 131 
#define  BT_PICCOLO 130 
#define  BT_SD64 129 
#define  BT_SPECTRUM 128 
 int /*<<< orphan*/  CL_CRT1B ; 
 int /*<<< orphan*/  CL_CRT51 ; 
 int /*<<< orphan*/  CL_GR2F ; 
 int /*<<< orphan*/  CL_GR31 ; 
 int /*<<< orphan*/  CL_GR33 ; 
 int /*<<< orphan*/  CL_GRB ; 
 int /*<<< orphan*/  CL_GRC ; 
 int /*<<< orphan*/  CL_GRD ; 
 int /*<<< orphan*/  CL_GRE ; 
 int /*<<< orphan*/  CL_POS102 ; 
 int /*<<< orphan*/  CL_SEQR10 ; 
 int /*<<< orphan*/  CL_SEQR11 ; 
 int /*<<< orphan*/  CL_SEQR12 ; 
 int /*<<< orphan*/  CL_SEQR13 ; 
 int /*<<< orphan*/  CL_SEQR16 ; 
 int /*<<< orphan*/  CL_SEQR17 ; 
 int /*<<< orphan*/  CL_SEQR18 ; 
 int /*<<< orphan*/  CL_SEQR6 ; 
 int /*<<< orphan*/  CL_SEQR7 ; 
 int /*<<< orphan*/  CL_SEQRF ; 
 int /*<<< orphan*/  CL_VSSM ; 
 int /*<<< orphan*/  CL_VSSM2 ; 
 int /*<<< orphan*/  VGA_ATC_COLOR_PAGE ; 
 int /*<<< orphan*/  VGA_ATC_MODE ; 
 int /*<<< orphan*/  VGA_ATC_OVERSCAN ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE0 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE1 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE2 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE3 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE4 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE5 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE6 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE7 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE8 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTE9 ; 
 int /*<<< orphan*/  VGA_ATC_PALETTEA ; 
 int /*<<< orphan*/  VGA_ATC_PALETTEB ; 
 int /*<<< orphan*/  VGA_ATC_PALETTEC ; 
 int /*<<< orphan*/  VGA_ATC_PALETTED ; 
 int /*<<< orphan*/  VGA_ATC_PALETTEE ; 
 int /*<<< orphan*/  VGA_ATC_PALETTEF ; 
 int /*<<< orphan*/  VGA_ATC_PLANE_ENABLE ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_END ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_HI ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LO ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_START ; 
 int /*<<< orphan*/  VGA_CRTC_PRESET_ROW ; 
 int /*<<< orphan*/  VGA_CRTC_UNDERLINE ; 
 int /*<<< orphan*/  VGA_GFX_BIT_MASK ; 
 int /*<<< orphan*/  VGA_GFX_COMPARE_MASK ; 
 int /*<<< orphan*/  VGA_GFX_COMPARE_VALUE ; 
 int /*<<< orphan*/  VGA_GFX_DATA_ROTATE ; 
 int /*<<< orphan*/  VGA_GFX_MISC ; 
 int /*<<< orphan*/  VGA_GFX_MODE ; 
 int /*<<< orphan*/  VGA_GFX_PLANE_READ ; 
 int /*<<< orphan*/  VGA_GFX_SR_ENABLE ; 
 int /*<<< orphan*/  VGA_GFX_SR_VALUE ; 
 int /*<<< orphan*/  VGA_PEL_MSK ; 
 int /*<<< orphan*/  VGA_SEQ_CHARACTER_MAP ; 
 int /*<<< orphan*/  VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_MEMORY_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_PLANE_WRITE ; 
 int /*<<< orphan*/  VGA_SEQ_RESET ; 
 int /*<<< orphan*/  WGen (struct cirrusfb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WHDR (struct cirrusfb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSFR (struct cirrusfb_info*,int) ; 
 int /*<<< orphan*/  WSFR2 (struct cirrusfb_info*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cirrusfb_board_info_rec* cirrusfb_board_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_laguna (struct cirrusfb_info*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vga_wattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_vgachip(struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;
	const struct cirrusfb_board_info_rec *bi;

	assert(cinfo != NULL);

	bi = &cirrusfb_board_info[cinfo->btype];

	/* reset board globally */
	switch (cinfo->btype) {
	case BT_PICCOLO:
		WSFR(cinfo, 0x01);
		udelay(500);
		WSFR(cinfo, 0x51);
		udelay(500);
		break;
	case BT_PICASSO:
		WSFR2(cinfo, 0xff);
		udelay(500);
		break;
	case BT_SD64:
	case BT_SPECTRUM:
		WSFR(cinfo, 0x1f);
		udelay(500);
		WSFR(cinfo, 0x4f);
		udelay(500);
		break;
	case BT_PICASSO4:
		/* disable flickerfixer */
		vga_wcrt(cinfo->regbase, CL_CRT51, 0x00);
		mdelay(100);
		/* mode */
		vga_wgfx(cinfo->regbase, CL_GR31, 0x00);
		/* fall through */
	case BT_GD5480:
		/* from Klaus' NetBSD driver: */
		vga_wgfx(cinfo->regbase, CL_GR2F, 0x00);
		/* fall through */
	case BT_ALPINE:
		/* put blitter into 542x compat */
		vga_wgfx(cinfo->regbase, CL_GR33, 0x00);
		break;

	case BT_LAGUNA:
	case BT_LAGUNAB:
		/* Nothing to do to reset the board. */
		break;

	default:
		dev_err(info->device, "Warning: Unknown board type\n");
		break;
	}

	/* make sure RAM size set by this point */
	assert(info->screen_size > 0);

	/* the P4 is not fully initialized here; I rely on it having been */
	/* inited under AmigaOS already, which seems to work just fine    */
	/* (Klaus advised to do it this way)			      */

	if (cinfo->btype != BT_PICASSO4) {
		WGen(cinfo, CL_VSSM, 0x10);	/* EGS: 0x16 */
		WGen(cinfo, CL_POS102, 0x01);
		WGen(cinfo, CL_VSSM, 0x08);	/* EGS: 0x0e */

		if (cinfo->btype != BT_SD64)
			WGen(cinfo, CL_VSSM2, 0x01);

		/* reset sequencer logic */
		vga_wseq(cinfo->regbase, VGA_SEQ_RESET, 0x03);

		/* FullBandwidth (video off) and 8/9 dot clock */
		vga_wseq(cinfo->regbase, VGA_SEQ_CLOCK_MODE, 0x21);

		/* "magic cookie" - doesn't make any sense to me.. */
/*      vga_wgfx(cinfo->regbase, CL_GRA, 0xce);   */
		/* unlock all extension registers */
		vga_wseq(cinfo->regbase, CL_SEQR6, 0x12);

		switch (cinfo->btype) {
		case BT_GD5480:
			vga_wseq(cinfo->regbase, CL_SEQRF, 0x98);
			break;
		case BT_ALPINE:
		case BT_LAGUNA:
		case BT_LAGUNAB:
			break;
		case BT_SD64:
#ifdef CONFIG_ZORRO
			vga_wseq(cinfo->regbase, CL_SEQRF, 0xb8);
#endif
			break;
		default:
			vga_wseq(cinfo->regbase, CL_SEQR16, 0x0f);
			vga_wseq(cinfo->regbase, CL_SEQRF, 0xb0);
			break;
		}
	}
	/* plane mask: nothing */
	vga_wseq(cinfo->regbase, VGA_SEQ_PLANE_WRITE, 0xff);
	/* character map select: doesn't even matter in gx mode */
	vga_wseq(cinfo->regbase, VGA_SEQ_CHARACTER_MAP, 0x00);
	/* memory mode: chain4, ext. memory */
	vga_wseq(cinfo->regbase, VGA_SEQ_MEMORY_MODE, 0x0a);

	/* controller-internal base address of video memory */
	if (bi->init_sr07)
		vga_wseq(cinfo->regbase, CL_SEQR7, bi->sr07);

	/*  vga_wseq(cinfo->regbase, CL_SEQR8, 0x00); */
	/* EEPROM control: shouldn't be necessary to write to this at all.. */

	/* graphics cursor X position (incomplete; position gives rem. 3 bits */
	vga_wseq(cinfo->regbase, CL_SEQR10, 0x00);
	/* graphics cursor Y position (..."... ) */
	vga_wseq(cinfo->regbase, CL_SEQR11, 0x00);
	/* graphics cursor attributes */
	vga_wseq(cinfo->regbase, CL_SEQR12, 0x00);
	/* graphics cursor pattern address */
	vga_wseq(cinfo->regbase, CL_SEQR13, 0x00);

	/* writing these on a P4 might give problems..  */
	if (cinfo->btype != BT_PICASSO4) {
		/* configuration readback and ext. color */
		vga_wseq(cinfo->regbase, CL_SEQR17, 0x00);
		/* signature generator */
		vga_wseq(cinfo->regbase, CL_SEQR18, 0x02);
	}

	/* Screen A preset row scan: none */
	vga_wcrt(cinfo->regbase, VGA_CRTC_PRESET_ROW, 0x00);
	/* Text cursor start: disable text cursor */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_START, 0x20);
	/* Text cursor end: - */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_END, 0x00);
	/* text cursor location high: 0 */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_HI, 0x00);
	/* text cursor location low: 0 */
	vga_wcrt(cinfo->regbase, VGA_CRTC_CURSOR_LO, 0x00);

	/* Underline Row scanline: - */
	vga_wcrt(cinfo->regbase, VGA_CRTC_UNDERLINE, 0x00);
	/* ### add 0x40 for text modes with > 30 MHz pixclock */
	/* ext. display controls: ext.adr. wrap */
	vga_wcrt(cinfo->regbase, CL_CRT1B, 0x02);

	/* Set/Reset registers: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_SR_VALUE, 0x00);
	/* Set/Reset enable: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_SR_ENABLE, 0x00);
	/* Color Compare: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_COMPARE_VALUE, 0x00);
	/* Data Rotate: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_DATA_ROTATE, 0x00);
	/* Read Map Select: - */
	vga_wgfx(cinfo->regbase, VGA_GFX_PLANE_READ, 0x00);
	/* Mode: conf. for 16/4/2 color mode, no odd/even, read/write mode 0 */
	vga_wgfx(cinfo->regbase, VGA_GFX_MODE, 0x00);
	/* Miscellaneous: memory map base address, graphics mode */
	vga_wgfx(cinfo->regbase, VGA_GFX_MISC, 0x01);
	/* Color Don't care: involve all planes */
	vga_wgfx(cinfo->regbase, VGA_GFX_COMPARE_MASK, 0x0f);
	/* Bit Mask: no mask at all */
	vga_wgfx(cinfo->regbase, VGA_GFX_BIT_MASK, 0xff);

	if (cinfo->btype == BT_ALPINE || cinfo->btype == BT_SD64 ||
	    is_laguna(cinfo))
		/* (5434 can't have bit 3 set for bitblt) */
		vga_wgfx(cinfo->regbase, CL_GRB, 0x20);
	else
	/* Graphics controller mode extensions: finer granularity,
	 * 8byte data latches
	 */
		vga_wgfx(cinfo->regbase, CL_GRB, 0x28);

	vga_wgfx(cinfo->regbase, CL_GRC, 0xff);	/* Color Key compare: - */
	vga_wgfx(cinfo->regbase, CL_GRD, 0x00);	/* Color Key compare mask: - */
	vga_wgfx(cinfo->regbase, CL_GRE, 0x00);	/* Miscellaneous control: - */
	/* Background color byte 1: - */
	/*  vga_wgfx (cinfo->regbase, CL_GR10, 0x00); */
	/*  vga_wgfx (cinfo->regbase, CL_GR11, 0x00); */

	/* Attribute Controller palette registers: "identity mapping" */
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE0, 0x00);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE1, 0x01);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE2, 0x02);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE3, 0x03);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE4, 0x04);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE5, 0x05);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE6, 0x06);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE7, 0x07);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE8, 0x08);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTE9, 0x09);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEA, 0x0a);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEB, 0x0b);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEC, 0x0c);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTED, 0x0d);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEE, 0x0e);
	vga_wattr(cinfo->regbase, VGA_ATC_PALETTEF, 0x0f);

	/* Attribute Controller mode: graphics mode */
	vga_wattr(cinfo->regbase, VGA_ATC_MODE, 0x01);
	/* Overscan color reg.: reg. 0 */
	vga_wattr(cinfo->regbase, VGA_ATC_OVERSCAN, 0x00);
	/* Color Plane enable: Enable all 4 planes */
	vga_wattr(cinfo->regbase, VGA_ATC_PLANE_ENABLE, 0x0f);
	/* Color Select: - */
	vga_wattr(cinfo->regbase, VGA_ATC_COLOR_PAGE, 0x00);

	WGen(cinfo, VGA_PEL_MSK, 0xff);	/* Pixel mask: no mask */

	/* BLT Start/status: Blitter reset */
	vga_wgfx(cinfo->regbase, CL_GR31, 0x04);
	/* - " -	   : "end-of-reset" */
	vga_wgfx(cinfo->regbase, CL_GR31, 0x00);

	/* misc... */
	WHDR(cinfo, 0);	/* Hidden DAC register: - */
	return;
}