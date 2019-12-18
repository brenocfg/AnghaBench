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
typedef  enum lcdc_load_mode { ____Placeholder_lcdc_load_mode } lcdc_load_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  OMAP_LCDC_CONTROL ; 
#define  OMAP_LCDC_LOAD_FRAME 130 
#define  OMAP_LCDC_LOAD_PALETTE 129 
#define  OMAP_LCDC_LOAD_PALETTE_AND_FRAME 128 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_load_mode(enum lcdc_load_mode mode)
{
	u32 l;

	l = omap_readl(OMAP_LCDC_CONTROL);
	l &= ~(3 << 20);
	switch (mode) {
	case OMAP_LCDC_LOAD_PALETTE:
		l |= 1 << 20;
		break;
	case OMAP_LCDC_LOAD_FRAME:
		l |= 2 << 20;
		break;
	case OMAP_LCDC_LOAD_PALETTE_AND_FRAME:
		break;
	default:
		BUG();
	}
	omap_writel(l, OMAP_LCDC_CONTROL);
}