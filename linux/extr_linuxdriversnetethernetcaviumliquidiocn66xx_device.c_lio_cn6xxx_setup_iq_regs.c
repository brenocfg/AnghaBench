#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct octeon_instr_queue {scalar_t__ inst_cnt_reg; int /*<<< orphan*/  reset_instr_cnt; scalar_t__ doorbell_reg; int /*<<< orphan*/  max_count; int /*<<< orphan*/  base_addr_dma; } ;
struct octeon_device {TYPE_2__* pci_dev; TYPE_1__* mmio; struct octeon_instr_queue** instr_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ hw_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_SLI_IQ_BASE_ADDR64 (size_t) ; 
 scalar_t__ CN6XXX_SLI_IQ_DOORBELL (size_t) ; 
 scalar_t__ CN6XXX_SLI_IQ_INSTR_COUNT (size_t) ; 
 int /*<<< orphan*/  CN6XXX_SLI_IQ_PKT_INSTR_HDR64 (size_t) ; 
 int /*<<< orphan*/  CN6XXX_SLI_IQ_SIZE (size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

void lio_cn6xxx_setup_iq_regs(struct octeon_device *oct, u32 iq_no)
{
	struct octeon_instr_queue *iq = oct->instr_queue[iq_no];

	octeon_write_csr64(oct, CN6XXX_SLI_IQ_PKT_INSTR_HDR64(iq_no), 0);

	/* Write the start of the input queue's ring and its size  */
	octeon_write_csr64(oct, CN6XXX_SLI_IQ_BASE_ADDR64(iq_no),
			   iq->base_addr_dma);
	octeon_write_csr(oct, CN6XXX_SLI_IQ_SIZE(iq_no), iq->max_count);

	/* Remember the doorbell & instruction count register addr for this
	 * queue
	 */
	iq->doorbell_reg = oct->mmio[0].hw_addr + CN6XXX_SLI_IQ_DOORBELL(iq_no);
	iq->inst_cnt_reg = oct->mmio[0].hw_addr
			   + CN6XXX_SLI_IQ_INSTR_COUNT(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbell reg @ 0x%p instcnt_reg @ 0x%p\n",
		iq_no, iq->doorbell_reg, iq->inst_cnt_reg);

	/* Store the current instruction counter
	 * (used in flush_iq calculation)
	 */
	iq->reset_instr_cnt = readl(iq->inst_cnt_reg);
}