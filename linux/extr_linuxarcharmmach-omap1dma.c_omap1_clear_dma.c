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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  OMAP_DMA_CCR_EN ; 
 int /*<<< orphan*/  dma_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap1_clear_dma(int lch)
{
	u32 l;

	l = dma_read(CCR, lch);
	l &= ~OMAP_DMA_CCR_EN;
	dma_write(l, CCR, lch);

	/* Clear pending interrupts */
	l = dma_read(CSR, lch);
}