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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct list_head {int dummy; } ;
struct fw_scsi_abrt_cls_wr {int /*<<< orphan*/  sub_opcode_to_chk_all_io; } ;
struct TYPE_2__ {int /*<<< orphan*/  sm_list; } ;
struct csio_ioreq {TYPE_1__ sm; int /*<<< orphan*/  wr_status; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;
struct csio_fl_dma_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ FW_SCSI_ABRT_CLS_WR ; 
 scalar_t__ FW_SCSI_ABRT_CLS_WR_SUB_OPCODE_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,char*,struct csio_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_put_scsi_ioreq_lock (struct csio_hw*,int /*<<< orphan*/ ,struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_scsi_aborted (struct csio_ioreq*,struct list_head*) ; 
 int /*<<< orphan*/  csio_scsi_closed (struct csio_ioreq*,struct list_head*) ; 
 void* csio_scsi_cmnd (struct csio_ioreq*) ; 
 struct csio_ioreq* csio_scsi_cmpl_handler (struct csio_hw*,void*,int /*<<< orphan*/ ,struct csio_fl_dma_buf*,int /*<<< orphan*/ *,scalar_t__**) ; 
 int /*<<< orphan*/  csio_scsi_completed (struct csio_ioreq*,struct list_head*) ; 
 scalar_t__ likely (struct csio_ioreq*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
csio_process_scsi_cmpl(struct csio_hw *hw, void *wr, uint32_t len,
			struct csio_fl_dma_buf *flb, void *cbfn_q)
{
	struct csio_ioreq *ioreq;
	uint8_t *scsiwr;
	uint8_t subop;
	void *cmnd;
	unsigned long flags;

	ioreq = csio_scsi_cmpl_handler(hw, wr, len, flb, NULL, &scsiwr);
	if (likely(ioreq)) {
		if (unlikely(*scsiwr == FW_SCSI_ABRT_CLS_WR)) {
			subop = FW_SCSI_ABRT_CLS_WR_SUB_OPCODE_GET(
					((struct fw_scsi_abrt_cls_wr *)
					    scsiwr)->sub_opcode_to_chk_all_io);

			csio_dbg(hw, "%s cmpl recvd ioreq:%p status:%d\n",
				    subop ? "Close" : "Abort",
				    ioreq, ioreq->wr_status);

			spin_lock_irqsave(&hw->lock, flags);
			if (subop)
				csio_scsi_closed(ioreq,
						 (struct list_head *)cbfn_q);
			else
				csio_scsi_aborted(ioreq,
						  (struct list_head *)cbfn_q);
			/*
			 * We call scsi_done for I/Os that driver thinks aborts
			 * have timed out. If there is a race caused by FW
			 * completing abort at the exact same time that the
			 * driver has deteced the abort timeout, the following
			 * check prevents calling of scsi_done twice for the
			 * same command: once from the eh_abort_handler, another
			 * from csio_scsi_isr_handler(). This also avoids the
			 * need to check if csio_scsi_cmnd(req) is NULL in the
			 * fast path.
			 */
			cmnd = csio_scsi_cmnd(ioreq);
			if (unlikely(cmnd == NULL))
				list_del_init(&ioreq->sm.sm_list);

			spin_unlock_irqrestore(&hw->lock, flags);

			if (unlikely(cmnd == NULL))
				csio_put_scsi_ioreq_lock(hw,
						csio_hw_to_scsim(hw), ioreq);
		} else {
			spin_lock_irqsave(&hw->lock, flags);
			csio_scsi_completed(ioreq, (struct list_head *)cbfn_q);
			spin_unlock_irqrestore(&hw->lock, flags);
		}
	}
}