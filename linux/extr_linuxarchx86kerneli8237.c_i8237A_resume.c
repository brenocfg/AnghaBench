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

/* Variables and functions */
 int /*<<< orphan*/  DMA1_RESET_REG ; 
 int /*<<< orphan*/  DMA2_RESET_REG ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  dma_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int,int) ; 
 int /*<<< orphan*/  set_dma_count (int,int) ; 

__attribute__((used)) static void i8237A_resume(void)
{
	unsigned long flags;
	int i;

	flags = claim_dma_lock();

	dma_outb(0, DMA1_RESET_REG);
	dma_outb(0, DMA2_RESET_REG);

	for (i = 0; i < 8; i++) {
		set_dma_addr(i, 0x000000);
		/* DMA count is a bit weird so this is not 0 */
		set_dma_count(i, 1);
	}

	/* Enable cascade DMA or channel 0-3 won't work */
	enable_dma(4);

	release_dma_lock(flags);
}