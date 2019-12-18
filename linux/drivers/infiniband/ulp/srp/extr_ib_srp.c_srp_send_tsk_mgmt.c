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
typedef  int /*<<< orphan*/  u64 ;
struct srp_tsk_mgmt {int tag; int /*<<< orphan*/  task_tag; int /*<<< orphan*/  tsk_mgmt_func; int /*<<< orphan*/  lun; int /*<<< orphan*/  opcode; } ;
struct srp_target_port {scalar_t__ qp_in_error; TYPE_2__* srp_host; struct srp_rport* rport; } ;
struct srp_rport {int /*<<< orphan*/  mutex; } ;
struct srp_rdma_ch {int tsk_mgmt_tag; int /*<<< orphan*/  tsk_mgmt_status; int /*<<< orphan*/  tsk_mgmt_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  connected; struct srp_target_port* target; } ;
struct srp_iu {int num_sge; int /*<<< orphan*/  dma; struct srp_tsk_mgmt* buf; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* srp_dev; } ;
struct TYPE_3__ {struct ib_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SRP_ABORT_TIMEOUT_MS ; 
 int /*<<< orphan*/  SRP_IU_TSK_MGMT ; 
 int SRP_TAG_TSK_MGMT ; 
 int /*<<< orphan*/  SRP_TSK_MGMT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct srp_iu* __srp_get_tx_iu (struct srp_rdma_ch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct srp_tsk_mgmt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ srp_post_send (struct srp_rdma_ch*,struct srp_iu*,int) ; 
 int /*<<< orphan*/  srp_put_tx_iu (struct srp_rdma_ch*,struct srp_iu*,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srp_send_tsk_mgmt(struct srp_rdma_ch *ch, u64 req_tag, u64 lun,
			     u8 func, u8 *status)
{
	struct srp_target_port *target = ch->target;
	struct srp_rport *rport = target->rport;
	struct ib_device *dev = target->srp_host->srp_dev->dev;
	struct srp_iu *iu;
	struct srp_tsk_mgmt *tsk_mgmt;
	int res;

	if (!ch->connected || target->qp_in_error)
		return -1;

	/*
	 * Lock the rport mutex to avoid that srp_create_ch_ib() is
	 * invoked while a task management function is being sent.
	 */
	mutex_lock(&rport->mutex);
	spin_lock_irq(&ch->lock);
	iu = __srp_get_tx_iu(ch, SRP_IU_TSK_MGMT);
	spin_unlock_irq(&ch->lock);

	if (!iu) {
		mutex_unlock(&rport->mutex);

		return -1;
	}

	iu->num_sge = 1;

	ib_dma_sync_single_for_cpu(dev, iu->dma, sizeof *tsk_mgmt,
				   DMA_TO_DEVICE);
	tsk_mgmt = iu->buf;
	memset(tsk_mgmt, 0, sizeof *tsk_mgmt);

	tsk_mgmt->opcode 	= SRP_TSK_MGMT;
	int_to_scsilun(lun, &tsk_mgmt->lun);
	tsk_mgmt->tsk_mgmt_func = func;
	tsk_mgmt->task_tag	= req_tag;

	spin_lock_irq(&ch->lock);
	ch->tsk_mgmt_tag = (ch->tsk_mgmt_tag + 1) | SRP_TAG_TSK_MGMT;
	tsk_mgmt->tag = ch->tsk_mgmt_tag;
	spin_unlock_irq(&ch->lock);

	init_completion(&ch->tsk_mgmt_done);

	ib_dma_sync_single_for_device(dev, iu->dma, sizeof *tsk_mgmt,
				      DMA_TO_DEVICE);
	if (srp_post_send(ch, iu, sizeof(*tsk_mgmt))) {
		srp_put_tx_iu(ch, iu, SRP_IU_TSK_MGMT);
		mutex_unlock(&rport->mutex);

		return -1;
	}
	res = wait_for_completion_timeout(&ch->tsk_mgmt_done,
					msecs_to_jiffies(SRP_ABORT_TIMEOUT_MS));
	if (res > 0 && status)
		*status = ch->tsk_mgmt_status;
	mutex_unlock(&rport->mutex);

	WARN_ON_ONCE(res < 0);

	return res > 0 ? 0 : -1;
}