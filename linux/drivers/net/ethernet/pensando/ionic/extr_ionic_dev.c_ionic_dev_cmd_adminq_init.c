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
struct TYPE_2__ {int /*<<< orphan*/  cq_ring_base; int /*<<< orphan*/  ring_base; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  intr_index; int /*<<< orphan*/  pid; int /*<<< orphan*/  flags; int /*<<< orphan*/  index; int /*<<< orphan*/  type; int /*<<< orphan*/  lif_index; int /*<<< orphan*/  opcode; } ;
union ionic_dev_cmd {TYPE_1__ q_init; } ;
typedef  int u16 ;
struct ionic_queue {int pid; int /*<<< orphan*/  base_pa; int /*<<< orphan*/  num_descs; int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
struct ionic_cq {int /*<<< orphan*/  base_pa; } ;
struct ionic_qcq {struct ionic_cq cq; struct ionic_queue q; } ;
struct ionic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_CMD_Q_INIT ; 
 int IONIC_QINIT_F_ENA ; 
 int IONIC_QINIT_F_IRQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_dev_cmd_go (struct ionic_dev*,union ionic_dev_cmd*) ; 

void ionic_dev_cmd_adminq_init(struct ionic_dev *idev, struct ionic_qcq *qcq,
			       u16 lif_index, u16 intr_index)
{
	struct ionic_queue *q = &qcq->q;
	struct ionic_cq *cq = &qcq->cq;

	union ionic_dev_cmd cmd = {
		.q_init.opcode = IONIC_CMD_Q_INIT,
		.q_init.lif_index = cpu_to_le16(lif_index),
		.q_init.type = q->type,
		.q_init.index = cpu_to_le32(q->index),
		.q_init.flags = cpu_to_le16(IONIC_QINIT_F_IRQ |
					    IONIC_QINIT_F_ENA),
		.q_init.pid = cpu_to_le16(q->pid),
		.q_init.intr_index = cpu_to_le16(intr_index),
		.q_init.ring_size = ilog2(q->num_descs),
		.q_init.ring_base = cpu_to_le64(q->base_pa),
		.q_init.cq_ring_base = cpu_to_le64(cq->base_pa),
	};

	ionic_dev_cmd_go(idev, &cmd);
}