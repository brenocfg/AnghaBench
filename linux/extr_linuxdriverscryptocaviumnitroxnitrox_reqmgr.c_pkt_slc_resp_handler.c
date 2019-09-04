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
struct TYPE_2__ {int resend; } ;
union nps_pkt_slc_cnts {int /*<<< orphan*/  value; TYPE_1__ s; } ;
struct nitrox_cmdq {int /*<<< orphan*/  backlog_qflush; int /*<<< orphan*/  backlog_count; } ;
struct bh_data {int /*<<< orphan*/  completion_cnt_csr_addr; struct nitrox_cmdq* cmdq; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  process_response_list (struct nitrox_cmdq*) ; 
 int /*<<< orphan*/  readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pkt_slc_resp_handler(unsigned long data)
{
	struct bh_data *bh = (void *)(uintptr_t)(data);
	struct nitrox_cmdq *cmdq = bh->cmdq;
	union nps_pkt_slc_cnts pkt_slc_cnts;

	/* read completion count */
	pkt_slc_cnts.value = readq(bh->completion_cnt_csr_addr);
	/* resend the interrupt if more work to do */
	pkt_slc_cnts.s.resend = 1;

	process_response_list(cmdq);

	/*
	 * clear the interrupt with resend bit enabled,
	 * MSI-X interrupt generates if Completion count > Threshold
	 */
	writeq(pkt_slc_cnts.value, bh->completion_cnt_csr_addr);
	/* order the writes */
	mmiowb();

	if (atomic_read(&cmdq->backlog_count))
		schedule_work(&cmdq->backlog_qflush);
}