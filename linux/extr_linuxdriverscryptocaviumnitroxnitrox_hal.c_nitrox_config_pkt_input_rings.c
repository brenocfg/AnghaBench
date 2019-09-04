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
struct TYPE_2__ {int /*<<< orphan*/  rsize; } ;
union nps_pkt_in_instr_rsize {int value; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int nr_queues; int /*<<< orphan*/  qlen; struct nitrox_cmdq* pkt_cmdqs; } ;
struct nitrox_cmdq {int dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_BADDRX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_RSIZEX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INT_LEVELSX (int) ; 
 int /*<<< orphan*/  enable_pkt_input_ring (struct nitrox_device*,int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_pkt_input_ring (struct nitrox_device*,int) ; 

void nitrox_config_pkt_input_rings(struct nitrox_device *ndev)
{
	int i;

	for (i = 0; i < ndev->nr_queues; i++) {
		struct nitrox_cmdq *cmdq = &ndev->pkt_cmdqs[i];
		union nps_pkt_in_instr_rsize pkt_in_rsize;
		u64 offset;

		reset_pkt_input_ring(ndev, i);

		/* configure ring base address 16-byte aligned,
		 * size and interrupt threshold.
		 */
		offset = NPS_PKT_IN_INSTR_BADDRX(i);
		nitrox_write_csr(ndev, offset, cmdq->dma);

		/* configure ring size */
		offset = NPS_PKT_IN_INSTR_RSIZEX(i);
		pkt_in_rsize.value = 0;
		pkt_in_rsize.s.rsize = ndev->qlen;
		nitrox_write_csr(ndev, offset, pkt_in_rsize.value);

		/* set high threshold for pkt input ring interrupts */
		offset = NPS_PKT_IN_INT_LEVELSX(i);
		nitrox_write_csr(ndev, offset, 0xffffffff);

		enable_pkt_input_ring(ndev, i);
	}
}