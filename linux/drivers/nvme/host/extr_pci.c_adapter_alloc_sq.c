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
typedef  int u16 ;
struct nvme_queue {int q_depth; int /*<<< orphan*/  sq_dma_addr; } ;
struct nvme_ctrl {int quirks; int /*<<< orphan*/  admin_q; } ;
struct nvme_dev {struct nvme_ctrl ctrl; } ;
struct TYPE_2__ {void* cqid; void* sq_flags; void* qsize; void* sqid; int /*<<< orphan*/  prp1; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ create_sq; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int NVME_QUEUE_PHYS_CONTIG ; 
 int NVME_QUIRK_MEDIUM_PRIO_SQ ; 
 int NVME_SQ_PRIO_MEDIUM ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_create_sq ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adapter_alloc_sq(struct nvme_dev *dev, u16 qid,
						struct nvme_queue *nvmeq)
{
	struct nvme_ctrl *ctrl = &dev->ctrl;
	struct nvme_command c;
	int flags = NVME_QUEUE_PHYS_CONTIG;

	/*
	 * Some drives have a bug that auto-enables WRRU if MEDIUM isn't
	 * set. Since URGENT priority is zeroes, it makes all queues
	 * URGENT.
	 */
	if (ctrl->quirks & NVME_QUIRK_MEDIUM_PRIO_SQ)
		flags |= NVME_SQ_PRIO_MEDIUM;

	/*
	 * Note: we (ab)use the fact that the prp fields survive if no data
	 * is attached to the request.
	 */
	memset(&c, 0, sizeof(c));
	c.create_sq.opcode = nvme_admin_create_sq;
	c.create_sq.prp1 = cpu_to_le64(nvmeq->sq_dma_addr);
	c.create_sq.sqid = cpu_to_le16(qid);
	c.create_sq.qsize = cpu_to_le16(nvmeq->q_depth - 1);
	c.create_sq.sq_flags = cpu_to_le16(flags);
	c.create_sq.cqid = cpu_to_le16(qid);

	return nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, NULL, 0);
}