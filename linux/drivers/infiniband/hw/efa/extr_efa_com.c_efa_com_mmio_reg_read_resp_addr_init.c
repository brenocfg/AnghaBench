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
struct efa_com_mmio_read {int read_resp_dma_addr; } ;
struct efa_com_dev {scalar_t__ reg_bar; struct efa_com_mmio_read mmio_read; } ;

/* Variables and functions */
 scalar_t__ EFA_REGS_MMIO_RESP_HI_OFF ; 
 scalar_t__ EFA_REGS_MMIO_RESP_LO_OFF ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void efa_com_mmio_reg_read_resp_addr_init(struct efa_com_dev *edev)
{
	struct efa_com_mmio_read *mmio_read = &edev->mmio_read;
	u32 addr_high;
	u32 addr_low;

	/* dma_addr_bits is unknown at this point */
	addr_high = (mmio_read->read_resp_dma_addr >> 32) & GENMASK(31, 0);
	addr_low = mmio_read->read_resp_dma_addr & GENMASK(31, 0);

	writel(addr_high, edev->reg_bar + EFA_REGS_MMIO_RESP_HI_OFF);
	writel(addr_low, edev->reg_bar + EFA_REGS_MMIO_RESP_LO_OFF);
}