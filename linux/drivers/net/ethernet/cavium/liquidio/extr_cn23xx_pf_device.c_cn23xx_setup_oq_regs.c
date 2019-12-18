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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct octeon_droq {int desc_ring_dma; size_t max_count; size_t buffer_size; int /*<<< orphan*/ * pkts_credit_reg; int /*<<< orphan*/ * pkts_sent_reg; } ;
struct TYPE_3__ {scalar_t__ pf_srn; } ;
struct octeon_device {int /*<<< orphan*/  msix_on; TYPE_2__* mmio; TYPE_1__ sriov_info; scalar_t__ chip; struct octeon_droq** droq; } ;
struct octeon_cn23xx_pf {int /*<<< orphan*/  conf; } ;
struct TYPE_4__ {scalar_t__ hw_addr; } ;

/* Variables and functions */
 scalar_t__ CFG_GET_OQ_INTR_PKT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_GET_OQ_INTR_TIME (int /*<<< orphan*/ ) ; 
 size_t CN23XX_PKT_OUTPUT_CTL_CENB ; 
 size_t CN23XX_PKT_OUTPUT_CTL_TENB ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_BASE_ADDR64 (size_t) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_BUFF_INFO_SIZE (size_t) ; 
 int CN23XX_SLI_OQ_PKTS_CREDIT (size_t) ; 
 int CN23XX_SLI_OQ_PKTS_SENT (size_t) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_PKT_CONTROL (size_t) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_PKT_INT_LEVELS (size_t) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_SIZE (size_t) ; 
 int cn23xx_pf_get_oq_ticks (struct octeon_device*,size_t) ; 
 size_t octeon_read_csr (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cn23xx_setup_oq_regs(struct octeon_device *oct, u32 oq_no)
{
	u32 reg_val;
	struct octeon_droq *droq = oct->droq[oq_no];
	struct octeon_cn23xx_pf *cn23xx = (struct octeon_cn23xx_pf *)oct->chip;
	u64 time_threshold;
	u64 cnt_threshold;

	oq_no += oct->sriov_info.pf_srn;

	octeon_write_csr64(oct, CN23XX_SLI_OQ_BASE_ADDR64(oq_no),
			   droq->desc_ring_dma);
	octeon_write_csr(oct, CN23XX_SLI_OQ_SIZE(oq_no), droq->max_count);

	octeon_write_csr(oct, CN23XX_SLI_OQ_BUFF_INFO_SIZE(oq_no),
			 droq->buffer_size);

	/* Get the mapped address of the pkt_sent and pkts_credit regs */
	droq->pkts_sent_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OQ_PKTS_SENT(oq_no);
	droq->pkts_credit_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OQ_PKTS_CREDIT(oq_no);

	if (!oct->msix_on) {
		/* Enable this output queue to generate Packet Timer Interrupt
		 */
		reg_val =
		    octeon_read_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no));
		reg_val |= CN23XX_PKT_OUTPUT_CTL_TENB;
		octeon_write_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no),
				 reg_val);

		/* Enable this output queue to generate Packet Count Interrupt
		 */
		reg_val =
		    octeon_read_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no));
		reg_val |= CN23XX_PKT_OUTPUT_CTL_CENB;
		octeon_write_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no),
				 reg_val);
	} else {
		time_threshold = cn23xx_pf_get_oq_ticks(
		    oct, (u32)CFG_GET_OQ_INTR_TIME(cn23xx->conf));
		cnt_threshold = (u32)CFG_GET_OQ_INTR_PKT(cn23xx->conf);

		octeon_write_csr64(
		    oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(oq_no),
		    ((time_threshold << 32 | cnt_threshold)));
	}
}