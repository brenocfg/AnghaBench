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
struct sas_task {int /*<<< orphan*/  task_state_lock; int /*<<< orphan*/  task_state_flags; struct hisi_sas_slot* lldd_task; struct domain_device* dev; } ;
struct hisi_sas_slot {int n_elem; int dlvry_queue; int dlvry_queue_slot; int is_internal; int /*<<< orphan*/  ready; struct hisi_sas_cmd_hdr* cmd_hdr; struct hisi_sas_port* port; struct sas_task* task; int /*<<< orphan*/  device_id; int /*<<< orphan*/  entry; int /*<<< orphan*/  delivery; } ;
struct hisi_sas_port {int dummy; } ;
struct hisi_sas_err_record {int dummy; } ;
struct hisi_sas_dq {int wr_point; int id; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct hisi_sas_device {int /*<<< orphan*/  device_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct hisi_sas_cmd_hdr {int dummy; } ;
struct hisi_hba {TYPE_1__* hw; struct hisi_sas_cmd_hdr** cmd_hdr; struct hisi_sas_slot* slot_info; int /*<<< orphan*/  flags; struct device* dev; } ;
struct domain_device {struct asd_sas_port* port; struct hisi_sas_device* lldd_dev; } ;
struct device {int dummy; } ;
struct asd_sas_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_delivery ) (struct hisi_sas_dq*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int HISI_SAS_COMMAND_TABLE_SZ ; 
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  HISI_SAS_REJECT_CMD_BIT ; 
 int /*<<< orphan*/  SAS_TASK_AT_INITIATOR ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct hisi_sas_cmd_hdr* hisi_sas_cmd_hdr_addr_mem (struct hisi_sas_slot*) ; 
 int hisi_sas_slot_index_alloc (struct hisi_hba*,int /*<<< orphan*/ *) ; 
 struct hisi_sas_cmd_hdr* hisi_sas_status_buf_addr_mem (struct hisi_sas_slot*) ; 
 int /*<<< orphan*/  hisi_sas_task_prep_abort (struct hisi_hba*,struct hisi_sas_slot*,int,int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hisi_sas_cmd_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct hisi_sas_dq*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hisi_sas_port* to_hisi_sas_port (struct asd_sas_port*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hisi_sas_internal_abort_task_exec(struct hisi_hba *hisi_hba, int device_id,
				  struct sas_task *task, int abort_flag,
				  int task_tag, struct hisi_sas_dq *dq)
{
	struct domain_device *device = task->dev;
	struct hisi_sas_device *sas_dev = device->lldd_dev;
	struct device *dev = hisi_hba->dev;
	struct hisi_sas_port *port;
	struct hisi_sas_slot *slot;
	struct asd_sas_port *sas_port = device->port;
	struct hisi_sas_cmd_hdr *cmd_hdr_base;
	int dlvry_queue_slot, dlvry_queue, n_elem = 0, rc, slot_idx;
	unsigned long flags;
	int wr_q_index;

	if (unlikely(test_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags)))
		return -EINVAL;

	if (!device->port)
		return -1;

	port = to_hisi_sas_port(sas_port);

	/* simply get a slot and send abort command */
	rc = hisi_sas_slot_index_alloc(hisi_hba, NULL);
	if (rc < 0)
		goto err_out;

	slot_idx = rc;
	slot = &hisi_hba->slot_info[slot_idx];

	spin_lock_irqsave(&dq->lock, flags);
	wr_q_index = dq->wr_point;
	dq->wr_point = (dq->wr_point + 1) % HISI_SAS_QUEUE_SLOTS;
	list_add_tail(&slot->delivery, &dq->list);
	spin_unlock_irqrestore(&dq->lock, flags);
	spin_lock_irqsave(&sas_dev->lock, flags);
	list_add_tail(&slot->entry, &sas_dev->list);
	spin_unlock_irqrestore(&sas_dev->lock, flags);

	dlvry_queue = dq->id;
	dlvry_queue_slot = wr_q_index;

	slot->device_id = sas_dev->device_id;
	slot->n_elem = n_elem;
	slot->dlvry_queue = dlvry_queue;
	slot->dlvry_queue_slot = dlvry_queue_slot;
	cmd_hdr_base = hisi_hba->cmd_hdr[dlvry_queue];
	slot->cmd_hdr = &cmd_hdr_base[dlvry_queue_slot];
	slot->task = task;
	slot->port = port;
	slot->is_internal = true;
	task->lldd_task = slot;

	memset(slot->cmd_hdr, 0, sizeof(struct hisi_sas_cmd_hdr));
	memset(hisi_sas_cmd_hdr_addr_mem(slot), 0, HISI_SAS_COMMAND_TABLE_SZ);
	memset(hisi_sas_status_buf_addr_mem(slot), 0,
	       sizeof(struct hisi_sas_err_record));

	hisi_sas_task_prep_abort(hisi_hba, slot, device_id,
				      abort_flag, task_tag);

	spin_lock_irqsave(&task->task_state_lock, flags);
	task->task_state_flags |= SAS_TASK_AT_INITIATOR;
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	WRITE_ONCE(slot->ready, 1);
	/* send abort command to the chip */
	spin_lock_irqsave(&dq->lock, flags);
	hisi_hba->hw->start_delivery(dq);
	spin_unlock_irqrestore(&dq->lock, flags);

	return 0;

err_out:
	dev_err(dev, "internal abort task prep: failed[%d]!\n", rc);

	return rc;
}