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
struct pxa168fb_info {int pix_fmt; int panel_rbswap; scalar_t__ reg_base; scalar_t__ active; } ;

/* Variables and functions */
 int CFG_GRA_ENA (int) ; 
 int CFG_GRA_ENA_MASK ; 
 scalar_t__ LCD_SPU_DMA_CTRL0 ; 
 int PIX_FMT_PSEUDOCOLOR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void set_dma_control0(struct pxa168fb_info *fbi)
{
	u32 x;

	/*
	 * Set bit to enable graphics DMA.
	 */
	x = readl(fbi->reg_base + LCD_SPU_DMA_CTRL0);
	x &= ~CFG_GRA_ENA_MASK;
	x |= fbi->active ? CFG_GRA_ENA(1) : CFG_GRA_ENA(0);

	/*
	 * If we are in a pseudo-color mode, we need to enable
	 * palette lookup.
	 */
	if (fbi->pix_fmt == PIX_FMT_PSEUDOCOLOR)
		x |= 0x10000000;

	/*
	 * Configure hardware pixel format.
	 */
	x &= ~(0xF << 16);
	x |= (fbi->pix_fmt >> 1) << 16;

	/*
	 * Check red and blue pixel swap.
	 * 1. source data swap
	 * 2. panel output data swap
	 */
	x &= ~(1 << 12);
	x |= ((fbi->pix_fmt & 1) ^ (fbi->panel_rbswap)) << 12;

	writel(x, fbi->reg_base + LCD_SPU_DMA_CTRL0);
}