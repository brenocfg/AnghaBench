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
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ poll_mode; } ;
struct octeon_droq {TYPE_1__ ops; } ;
struct TYPE_4__ {int oq; } ;
struct octeon_device {int droq_intr; TYPE_2__ io_qmask; scalar_t__ chip; struct octeon_droq** droq; } ;
struct octeon_cn6xxx {int /*<<< orphan*/  lock_for_droq_int_enb_reg; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int CN6XXX_SLI_PKT_CNT_INT ; 
 int CN6XXX_SLI_PKT_CNT_INT_ENB ; 
 int CN6XXX_SLI_PKT_TIME_INT ; 
 int CN6XXX_SLI_PKT_TIME_INT_ENB ; 
 int MAX_OCTEON_OUTPUT_QUEUES (struct octeon_device*) ; 
 int octeon_droq_check_hw_for_pkts (struct octeon_droq*) ; 
 int octeon_read_csr (struct octeon_device*,int) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lio_cn6xxx_process_droq_intr_regs(struct octeon_device *oct)
{
	struct octeon_droq *droq;
	int oq_no;
	u32 pkt_count, droq_time_mask, droq_mask, droq_int_enb;
	u32 droq_cnt_enb, droq_cnt_mask;

	droq_cnt_enb = octeon_read_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB);
	droq_cnt_mask = octeon_read_csr(oct, CN6XXX_SLI_PKT_CNT_INT);
	droq_mask = droq_cnt_mask & droq_cnt_enb;

	droq_time_mask = octeon_read_csr(oct, CN6XXX_SLI_PKT_TIME_INT);
	droq_int_enb = octeon_read_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB);
	droq_mask |= (droq_time_mask & droq_int_enb);

	droq_mask &= oct->io_qmask.oq;

	oct->droq_intr = 0;

	for (oq_no = 0; oq_no < MAX_OCTEON_OUTPUT_QUEUES(oct); oq_no++) {
		if (!(droq_mask & BIT_ULL(oq_no)))
			continue;

		droq = oct->droq[oq_no];
		pkt_count = octeon_droq_check_hw_for_pkts(droq);
		if (pkt_count) {
			oct->droq_intr |= BIT_ULL(oq_no);
			if (droq->ops.poll_mode) {
				u32 value;
				u32 reg;

				struct octeon_cn6xxx *cn6xxx =
					(struct octeon_cn6xxx *)oct->chip;

				/* disable interrupts for this droq */
				spin_lock
					(&cn6xxx->lock_for_droq_int_enb_reg);
				reg = CN6XXX_SLI_PKT_TIME_INT_ENB;
				value = octeon_read_csr(oct, reg);
				value &= ~(1 << oq_no);
				octeon_write_csr(oct, reg, value);
				reg = CN6XXX_SLI_PKT_CNT_INT_ENB;
				value = octeon_read_csr(oct, reg);
				value &= ~(1 << oq_no);
				octeon_write_csr(oct, reg, value);

				spin_unlock(&cn6xxx->lock_for_droq_int_enb_reg);
			}
		}
	}

	droq_time_mask &= oct->io_qmask.oq;
	droq_cnt_mask &= oct->io_qmask.oq;

	/* Reset the PKT_CNT/TIME_INT registers. */
	if (droq_time_mask)
		octeon_write_csr(oct, CN6XXX_SLI_PKT_TIME_INT, droq_time_mask);

	if (droq_cnt_mask)      /* reset PKT_CNT register:66xx */
		octeon_write_csr(oct, CN6XXX_SLI_PKT_CNT_INT, droq_cnt_mask);

	return 0;
}