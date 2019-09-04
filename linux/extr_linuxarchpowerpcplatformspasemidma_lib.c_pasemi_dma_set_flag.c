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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_FLAGS ; 
 int /*<<< orphan*/  PAS_DMA_TXF_SFLG0 ; 
 int /*<<< orphan*/  PAS_DMA_TXF_SFLG1 ; 
 int /*<<< orphan*/  pasemi_write_dma_reg (int /*<<< orphan*/ ,int) ; 

void pasemi_dma_set_flag(int flag)
{
	BUG_ON(flag >= MAX_FLAGS);
	if (flag < 32)
		pasemi_write_dma_reg(PAS_DMA_TXF_SFLG0, 1 << flag);
	else
		pasemi_write_dma_reg(PAS_DMA_TXF_SFLG1, 1 << flag);
}