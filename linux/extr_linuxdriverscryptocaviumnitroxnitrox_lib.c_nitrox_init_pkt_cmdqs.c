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
typedef  int /*<<< orphan*/  u64 ;
struct nps_pkt_instr {int dummy; } ;
struct nitrox_device {int nr_queues; struct nitrox_cmdq* pkt_cmdqs; } ;
struct nitrox_cmdq {int qno; int instr_size; int /*<<< orphan*/  dbell_csr_addr; struct nitrox_device* ndev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NITROX_CSR_ADDR (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_BAOFF_DBELLX (int) ; 
 int cmdq_common_init (struct nitrox_cmdq*) ; 
 struct nitrox_cmdq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_cleanup_pkt_cmdqs (struct nitrox_device*) ; 

__attribute__((used)) static int nitrox_init_pkt_cmdqs(struct nitrox_device *ndev)
{
	int i, err, size;

	size = ndev->nr_queues * sizeof(struct nitrox_cmdq);
	ndev->pkt_cmdqs = kzalloc(size, GFP_KERNEL);
	if (!ndev->pkt_cmdqs)
		return -ENOMEM;

	for (i = 0; i < ndev->nr_queues; i++) {
		struct nitrox_cmdq *cmdq;
		u64 offset;

		cmdq = &ndev->pkt_cmdqs[i];
		cmdq->ndev = ndev;
		cmdq->qno = i;
		cmdq->instr_size = sizeof(struct nps_pkt_instr);

		offset = NPS_PKT_IN_INSTR_BAOFF_DBELLX(i);
		/* SE ring doorbell address for this queue */
		cmdq->dbell_csr_addr = NITROX_CSR_ADDR(ndev, offset);

		err = cmdq_common_init(cmdq);
		if (err)
			goto pkt_cmdq_fail;
	}
	return 0;

pkt_cmdq_fail:
	nitrox_cleanup_pkt_cmdqs(ndev);
	return err;
}