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
typedef  size_t u32 ;
struct octeon_droq {size_t max_count; size_t buffer_size; scalar_t__ pkts_credit_reg; scalar_t__ pkts_sent_reg; int /*<<< orphan*/  desc_ring_dma; } ;
struct octeon_device {TYPE_1__* mmio; struct octeon_droq** droq; } ;
struct TYPE_2__ {scalar_t__ hw_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_SLI_OQ_BASE_ADDR64 (size_t) ; 
 int /*<<< orphan*/  CN6XXX_SLI_OQ_BUFF_INFO_SIZE (size_t) ; 
 scalar_t__ CN6XXX_SLI_OQ_PKTS_CREDIT (size_t) ; 
 scalar_t__ CN6XXX_SLI_OQ_PKTS_SENT (size_t) ; 
 int /*<<< orphan*/  CN6XXX_SLI_OQ_SIZE (size_t) ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_CNT_INT_ENB ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_TIME_INT_ENB ; 
 size_t octeon_read_csr (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lio_cn6xxx_setup_oq_regs(struct octeon_device *oct, u32 oq_no)
{
	u32 intr;
	struct octeon_droq *droq = oct->droq[oq_no];

	octeon_write_csr64(oct, CN6XXX_SLI_OQ_BASE_ADDR64(oq_no),
			   droq->desc_ring_dma);
	octeon_write_csr(oct, CN6XXX_SLI_OQ_SIZE(oq_no), droq->max_count);

	octeon_write_csr(oct, CN6XXX_SLI_OQ_BUFF_INFO_SIZE(oq_no),
			 droq->buffer_size);

	/* Get the mapped address of the pkt_sent and pkts_credit regs */
	droq->pkts_sent_reg =
		oct->mmio[0].hw_addr + CN6XXX_SLI_OQ_PKTS_SENT(oq_no);
	droq->pkts_credit_reg =
		oct->mmio[0].hw_addr + CN6XXX_SLI_OQ_PKTS_CREDIT(oq_no);

	/* Enable this output queue to generate Packet Timer Interrupt */
	intr = octeon_read_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB);
	intr |= (1 << oq_no);
	octeon_write_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB, intr);

	/* Enable this output queue to generate Packet Timer Interrupt */
	intr = octeon_read_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB);
	intr |= (1 << oq_no);
	octeon_write_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB, intr);
}