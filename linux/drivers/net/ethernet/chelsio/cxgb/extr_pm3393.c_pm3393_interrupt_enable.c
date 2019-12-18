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
typedef  int /*<<< orphan*/  u32 ;
struct cmac {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_PL_ENABLE ; 
 int /*<<< orphan*/  F_PL_INTR_EXT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_GLOBAL_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_0 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_1 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_2 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_3 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IDU_INTERRUPT_MASK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_MASK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4ODP_INTERRUPT_MASK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXOAM_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_CONFIG_3 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXOAM_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXXG_CONFIG_3 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XRF_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XTEF_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pm3393_interrupt_enable(struct cmac *cmac)
{
	u32 pl_intr;

	/* PM3393 - Enabling all hardware block interrupts.
	 */
	pmwrite(cmac, SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_ENABLE, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_XRF_INTERRUPT_ENABLE, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_ENABLE, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_RXOAM_INTERRUPT_ENABLE, 0xffff);

	/* Don't interrupt on statistics overflow, we are polling */
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_0, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_1, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_2, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_3, 0);

	pmwrite(cmac, SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_ENABLE, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_PL4ODP_INTERRUPT_MASK, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_XTEF_INTERRUPT_ENABLE, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_TXOAM_INTERRUPT_ENABLE, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_3, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_MASK, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_3, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_PL4IDU_INTERRUPT_MASK, 0xffff);
	pmwrite(cmac, SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_ENABLE, 0xffff);

	/* PM3393 - Global interrupt enable
	 */
	/* TBD XXX Disable for now until we figure out why error interrupts keep asserting. */
	pmwrite(cmac, SUNI1x10GEXP_REG_GLOBAL_INTERRUPT_ENABLE,
		0 /*SUNI1x10GEXP_BITMSK_TOP_INTE */ );

	/* TERMINATOR - PL_INTERUPTS_EXT */
	pl_intr = readl(cmac->adapter->regs + A_PL_ENABLE);
	pl_intr |= F_PL_INTR_EXT;
	writel(pl_intr, cmac->adapter->regs + A_PL_ENABLE);
	return 0;
}