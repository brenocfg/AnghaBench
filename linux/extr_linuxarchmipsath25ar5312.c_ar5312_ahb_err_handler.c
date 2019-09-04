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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR5312_DMA1 ; 
 int /*<<< orphan*/  AR5312_DMAADDR ; 
 int /*<<< orphan*/  AR5312_PROC1 ; 
 int /*<<< orphan*/  AR5312_PROCADDR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ar5312_rst_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_restart (char*) ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ar5312_ahb_err_handler(int cpl, void *dev_id)
{
	u32 proc1 = ar5312_rst_reg_read(AR5312_PROC1);
	u32 proc_addr = ar5312_rst_reg_read(AR5312_PROCADDR); /* clears error */
	u32 dma1 = ar5312_rst_reg_read(AR5312_DMA1);
	u32 dma_addr = ar5312_rst_reg_read(AR5312_DMAADDR);   /* clears error */

	pr_emerg("AHB interrupt: PROCADDR=0x%8.8x PROC1=0x%8.8x DMAADDR=0x%8.8x DMA1=0x%8.8x\n",
		 proc_addr, proc1, dma_addr, dma1);

	machine_restart("AHB error"); /* Catastrophic failure */
	return IRQ_HANDLED;
}