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
typedef  scalar_t__ u32 ;
struct octeon_instr_queue {int /*<<< orphan*/  inst_cnt_reg; struct octeon_device* oct_dev; int /*<<< orphan*/  lock; scalar_t__ pkts_processed; int /*<<< orphan*/  pkt_in_done; } ;
struct octeon_droq {int /*<<< orphan*/  pkts_sent_reg; struct octeon_device* oct_dev; scalar_t__ pkt_count; int /*<<< orphan*/  pkts_pending; } ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int CN23XX_INTR_RESEND ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

void lio_enable_irq(struct octeon_droq *droq, struct octeon_instr_queue *iq)
{
	u64 instr_cnt;
	u32 pkts_pend;
	struct octeon_device *oct = NULL;

	/* the whole thing needs to be atomic, ideally */
	if (droq) {
		pkts_pend = (u32)atomic_read(&droq->pkts_pending);
		writel(droq->pkt_count - pkts_pend, droq->pkts_sent_reg);
		droq->pkt_count = pkts_pend;
		oct = droq->oct_dev;
	}
	if (iq) {
		spin_lock_bh(&iq->lock);
		writel(iq->pkts_processed, iq->inst_cnt_reg);
		iq->pkt_in_done -= iq->pkts_processed;
		iq->pkts_processed = 0;
		/* this write needs to be flushed before we release the lock */
		spin_unlock_bh(&iq->lock);
		oct = iq->oct_dev;
	}
	/*write resend. Writing RESEND in SLI_PKTX_CNTS should be enough
	 *to trigger tx interrupts as well, if they are pending.
	 */
	if (oct && (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct))) {
		if (droq)
			writeq(CN23XX_INTR_RESEND, droq->pkts_sent_reg);
		/*we race with firmrware here. read and write the IN_DONE_CNTS*/
		else if (iq) {
			instr_cnt =  readq(iq->inst_cnt_reg);
			writeq(((instr_cnt & 0xFFFFFFFF00000000ULL) |
				CN23XX_INTR_RESEND),
			       iq->inst_cnt_reg);
		}
	}
}