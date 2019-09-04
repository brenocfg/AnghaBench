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
typedef  int u16 ;
struct TYPE_2__ {int data_type; long vxres; unsigned long xres; int xscale; int yscale; int rotate; unsigned long yres; scalar_t__ mirror; int /*<<< orphan*/ * callback; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OMAP1510_DMA_LCD_BOT_F1_L ; 
 int /*<<< orphan*/  OMAP1510_DMA_LCD_BOT_F1_U ; 
 int /*<<< orphan*/  OMAP1510_DMA_LCD_TOP_F1_L ; 
 int /*<<< orphan*/  OMAP1510_DMA_LCD_TOP_F1_U ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_BOT_B1_L ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_BOT_B1_U ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_CCR ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_CSDP ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_CTRL ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_SRC_EI_B1 ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_SRC_EN_B1 ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_SRC_FI_B1_L ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_SRC_FI_B1_U ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_SRC_FN_B1 ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_TOP_B1_L ; 
 int /*<<< orphan*/  OMAP1610_DMA_LCD_TOP_B1_U ; 
#define  OMAP_DMA_DATA_TYPE_S16 130 
#define  OMAP_DMA_DATA_TYPE_S32 129 
#define  OMAP_DMA_DATA_TYPE_S8 128 
 scalar_t__ cpu_is_omap15xx () ; 
 TYPE_1__ lcd_dma ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_b1_regs(void)
{
	unsigned long top, bottom;
	int es;
	u16 w;
	unsigned long en, fn;
	long ei, fi;
	unsigned long vxres;
	unsigned int xscale, yscale;

	switch (lcd_dma.data_type) {
	case OMAP_DMA_DATA_TYPE_S8:
		es = 1;
		break;
	case OMAP_DMA_DATA_TYPE_S16:
		es = 2;
		break;
	case OMAP_DMA_DATA_TYPE_S32:
		es = 4;
		break;
	default:
		BUG();
		return;
	}

	vxres = lcd_dma.vxres ? lcd_dma.vxres : lcd_dma.xres;
	xscale = lcd_dma.xscale ? lcd_dma.xscale : 1;
	yscale = lcd_dma.yscale ? lcd_dma.yscale : 1;
	BUG_ON(vxres < lcd_dma.xres);

#define PIXADDR(x, y) (lcd_dma.addr +					\
		((y) * vxres * yscale + (x) * xscale) * es)
#define PIXSTEP(sx, sy, dx, dy) (PIXADDR(dx, dy) - PIXADDR(sx, sy) - es + 1)

	switch (lcd_dma.rotate) {
	case 0:
		if (!lcd_dma.mirror) {
			top = PIXADDR(0, 0);
			bottom = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			/* 1510 DMA requires the bottom address to be 2 more
			 * than the actual last memory access location. */
			if (cpu_is_omap15xx() &&
				lcd_dma.data_type == OMAP_DMA_DATA_TYPE_S32)
					bottom += 2;
			ei = PIXSTEP(0, 0, 1, 0);
			fi = PIXSTEP(lcd_dma.xres - 1, 0, 0, 1);
		} else {
			top = PIXADDR(lcd_dma.xres - 1, 0);
			bottom = PIXADDR(0, lcd_dma.yres - 1);
			ei = PIXSTEP(1, 0, 0, 0);
			fi = PIXSTEP(0, 0, lcd_dma.xres - 1, 1);
		}
		en = lcd_dma.xres;
		fn = lcd_dma.yres;
		break;
	case 90:
		if (!lcd_dma.mirror) {
			top = PIXADDR(0, lcd_dma.yres - 1);
			bottom = PIXADDR(lcd_dma.xres - 1, 0);
			ei = PIXSTEP(0, 1, 0, 0);
			fi = PIXSTEP(0, 0, 1, lcd_dma.yres - 1);
		} else {
			top = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			bottom = PIXADDR(0, 0);
			ei = PIXSTEP(0, 1, 0, 0);
			fi = PIXSTEP(1, 0, 0, lcd_dma.yres - 1);
		}
		en = lcd_dma.yres;
		fn = lcd_dma.xres;
		break;
	case 180:
		if (!lcd_dma.mirror) {
			top = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			bottom = PIXADDR(0, 0);
			ei = PIXSTEP(1, 0, 0, 0);
			fi = PIXSTEP(0, 1, lcd_dma.xres - 1, 0);
		} else {
			top = PIXADDR(0, lcd_dma.yres - 1);
			bottom = PIXADDR(lcd_dma.xres - 1, 0);
			ei = PIXSTEP(0, 0, 1, 0);
			fi = PIXSTEP(lcd_dma.xres - 1, 1, 0, 0);
		}
		en = lcd_dma.xres;
		fn = lcd_dma.yres;
		break;
	case 270:
		if (!lcd_dma.mirror) {
			top = PIXADDR(lcd_dma.xres - 1, 0);
			bottom = PIXADDR(0, lcd_dma.yres - 1);
			ei = PIXSTEP(0, 0, 0, 1);
			fi = PIXSTEP(1, lcd_dma.yres - 1, 0, 0);
		} else {
			top = PIXADDR(0, 0);
			bottom = PIXADDR(lcd_dma.xres - 1, lcd_dma.yres - 1);
			ei = PIXSTEP(0, 0, 0, 1);
			fi = PIXSTEP(0, lcd_dma.yres - 1, 1, 0);
		}
		en = lcd_dma.yres;
		fn = lcd_dma.xres;
		break;
	default:
		BUG();
		return;	/* Suppress warning about uninitialized vars */
	}

	if (cpu_is_omap15xx()) {
		omap_writew(top >> 16, OMAP1510_DMA_LCD_TOP_F1_U);
		omap_writew(top, OMAP1510_DMA_LCD_TOP_F1_L);
		omap_writew(bottom >> 16, OMAP1510_DMA_LCD_BOT_F1_U);
		omap_writew(bottom, OMAP1510_DMA_LCD_BOT_F1_L);

		return;
	}

	/* 1610 regs */
	omap_writew(top >> 16, OMAP1610_DMA_LCD_TOP_B1_U);
	omap_writew(top, OMAP1610_DMA_LCD_TOP_B1_L);
	omap_writew(bottom >> 16, OMAP1610_DMA_LCD_BOT_B1_U);
	omap_writew(bottom, OMAP1610_DMA_LCD_BOT_B1_L);

	omap_writew(en, OMAP1610_DMA_LCD_SRC_EN_B1);
	omap_writew(fn, OMAP1610_DMA_LCD_SRC_FN_B1);

	w = omap_readw(OMAP1610_DMA_LCD_CSDP);
	w &= ~0x03;
	w |= lcd_dma.data_type;
	omap_writew(w, OMAP1610_DMA_LCD_CSDP);

	w = omap_readw(OMAP1610_DMA_LCD_CTRL);
	/* Always set the source port as SDRAM for now*/
	w &= ~(0x03 << 6);
	if (lcd_dma.callback != NULL)
		w |= 1 << 1;		/* Block interrupt enable */
	else
		w &= ~(1 << 1);
	omap_writew(w, OMAP1610_DMA_LCD_CTRL);

	if (!(lcd_dma.rotate || lcd_dma.mirror ||
	      lcd_dma.vxres || lcd_dma.xscale || lcd_dma.yscale))
		return;

	w = omap_readw(OMAP1610_DMA_LCD_CCR);
	/* Set the double-indexed addressing mode */
	w |= (0x03 << 12);
	omap_writew(w, OMAP1610_DMA_LCD_CCR);

	omap_writew(ei, OMAP1610_DMA_LCD_SRC_EI_B1);
	omap_writew(fi >> 16, OMAP1610_DMA_LCD_SRC_FI_B1_U);
	omap_writew(fi, OMAP1610_DMA_LCD_SRC_FI_B1_L);
}