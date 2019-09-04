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
typedef  int /*<<< orphan*/  u8 ;
struct nitrox_softreq {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  status; int /*<<< orphan*/  instr; struct nitrox_device* ndev; } ;
struct nitrox_device {int /*<<< orphan*/  qlen; } ;
struct nitrox_cmdq {int write_idx; int instr_size; int /*<<< orphan*/  cmdq_lock; int /*<<< orphan*/  dbell_csr_addr; int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_POSTED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int incr_index (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  response_list_add (struct nitrox_softreq*,struct nitrox_cmdq*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void post_se_instr(struct nitrox_softreq *sr,
			  struct nitrox_cmdq *cmdq)
{
	struct nitrox_device *ndev = sr->ndev;
	int idx;
	u8 *ent;

	spin_lock_bh(&cmdq->cmdq_lock);

	idx = cmdq->write_idx;
	/* copy the instruction */
	ent = cmdq->head + (idx * cmdq->instr_size);
	memcpy(ent, &sr->instr, cmdq->instr_size);

	atomic_set(&sr->status, REQ_POSTED);
	response_list_add(sr, cmdq);
	sr->tstamp = jiffies;
	/* flush the command queue updates */
	dma_wmb();

	/* Ring doorbell with count 1 */
	writeq(1, cmdq->dbell_csr_addr);
	/* orders the doorbell rings */
	mmiowb();

	cmdq->write_idx = incr_index(idx, 1, ndev->qlen);

	spin_unlock_bh(&cmdq->cmdq_lock);
}