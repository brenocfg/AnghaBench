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
typedef  int u64 ;
struct octeon_device {int /*<<< orphan*/  int_status; scalar_t__ chip; } ;
struct octeon_cn6xxx {int /*<<< orphan*/  intr_sum_reg64; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CN6XXX_INTR_DMA0_FORCE ; 
 int CN6XXX_INTR_DMA1_FORCE ; 
 int CN6XXX_INTR_ERR ; 
 int CN6XXX_INTR_PKT_DATA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OCT_DEV_INTR_DMA0_FORCE ; 
 int /*<<< orphan*/  OCT_DEV_INTR_DMA1_FORCE ; 
 int /*<<< orphan*/  OCT_DEV_INTR_PKT_DATA ; 
 int /*<<< orphan*/  lio_cn6xxx_process_droq_intr_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_cn6xxx_process_pcie_error_intr (struct octeon_device*,int) ; 
 int readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

irqreturn_t lio_cn6xxx_process_interrupt_regs(void *dev)
{
	struct octeon_device *oct = (struct octeon_device *)dev;
	struct octeon_cn6xxx *cn6xxx = (struct octeon_cn6xxx *)oct->chip;
	u64 intr64;

	intr64 = readq(cn6xxx->intr_sum_reg64);

	/* If our device has interrupted, then proceed.
	 * Also check for all f's if interrupt was triggered on an error
	 * and the PCI read fails.
	 */
	if (!intr64 || (intr64 == 0xFFFFFFFFFFFFFFFFULL))
		return IRQ_NONE;

	oct->int_status = 0;

	if (intr64 & CN6XXX_INTR_ERR)
		lio_cn6xxx_process_pcie_error_intr(oct, intr64);

	if (intr64 & CN6XXX_INTR_PKT_DATA) {
		lio_cn6xxx_process_droq_intr_regs(oct);
		oct->int_status |= OCT_DEV_INTR_PKT_DATA;
	}

	if (intr64 & CN6XXX_INTR_DMA0_FORCE)
		oct->int_status |= OCT_DEV_INTR_DMA0_FORCE;

	if (intr64 & CN6XXX_INTR_DMA1_FORCE)
		oct->int_status |= OCT_DEV_INTR_DMA1_FORCE;

	/* Clear the current interrupts */
	writeq(intr64, cn6xxx->intr_sum_reg64);

	return IRQ_HANDLED;
}