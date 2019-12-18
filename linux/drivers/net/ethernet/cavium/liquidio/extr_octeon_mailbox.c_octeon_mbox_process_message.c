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
struct TYPE_3__ {int /*<<< orphan*/  resp_needed; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct octeon_mbox_cmd {int recv_status; TYPE_2__ msg; int /*<<< orphan*/  fn_arg; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,struct octeon_mbox_cmd*,int /*<<< orphan*/ ) ;} ;
struct octeon_mbox {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  mbox_read_reg; int /*<<< orphan*/  mbox_req; int /*<<< orphan*/  oct_dev; int /*<<< orphan*/  mbox_resp; } ;

/* Variables and functions */
 int OCTEON_MBOX_STATE_ERROR ; 
 void* OCTEON_MBOX_STATE_IDLE ; 
 int OCTEON_MBOX_STATE_REQUEST_RECEIVED ; 
 int OCTEON_MBOX_STATE_RESPONSE_PENDING ; 
 int OCTEON_MBOX_STATE_RESPONSE_RECEIVED ; 
 int OCTEON_MBOX_STATE_RESPONSE_RECEIVING ; 
 int /*<<< orphan*/  OCTEON_PFVFSIG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (struct octeon_mbox_cmd*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octeon_mbox_process_cmd (struct octeon_mbox*,struct octeon_mbox_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct octeon_mbox_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct octeon_mbox_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int octeon_mbox_process_message(struct octeon_mbox *mbox)
{
	struct octeon_mbox_cmd mbox_cmd;
	unsigned long flags;

	spin_lock_irqsave(&mbox->lock, flags);

	if (mbox->state & OCTEON_MBOX_STATE_ERROR) {
		if (mbox->state & (OCTEON_MBOX_STATE_RESPONSE_PENDING |
				   OCTEON_MBOX_STATE_RESPONSE_RECEIVING)) {
			memcpy(&mbox_cmd, &mbox->mbox_resp,
			       sizeof(struct octeon_mbox_cmd));
			mbox->state = OCTEON_MBOX_STATE_IDLE;
			writeq(OCTEON_PFVFSIG, mbox->mbox_read_reg);
			spin_unlock_irqrestore(&mbox->lock, flags);
			mbox_cmd.recv_status = 1;
			if (mbox_cmd.fn)
				mbox_cmd.fn(mbox->oct_dev, &mbox_cmd,
					    mbox_cmd.fn_arg);
			return 0;
		}

		mbox->state = OCTEON_MBOX_STATE_IDLE;
		writeq(OCTEON_PFVFSIG, mbox->mbox_read_reg);
		spin_unlock_irqrestore(&mbox->lock, flags);
		return 0;
	}

	if (mbox->state & OCTEON_MBOX_STATE_RESPONSE_RECEIVED) {
		memcpy(&mbox_cmd, &mbox->mbox_resp,
		       sizeof(struct octeon_mbox_cmd));
		mbox->state = OCTEON_MBOX_STATE_IDLE;
		writeq(OCTEON_PFVFSIG, mbox->mbox_read_reg);
		spin_unlock_irqrestore(&mbox->lock, flags);
		mbox_cmd.recv_status = 0;
		if (mbox_cmd.fn)
			mbox_cmd.fn(mbox->oct_dev, &mbox_cmd, mbox_cmd.fn_arg);
		return 0;
	}

	if (mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVED) {
		memcpy(&mbox_cmd, &mbox->mbox_req,
		       sizeof(struct octeon_mbox_cmd));
		if (!mbox_cmd.msg.s.resp_needed) {
			mbox->state &= ~OCTEON_MBOX_STATE_REQUEST_RECEIVED;
			if (!(mbox->state &
			      OCTEON_MBOX_STATE_RESPONSE_PENDING))
				mbox->state = OCTEON_MBOX_STATE_IDLE;
			writeq(OCTEON_PFVFSIG, mbox->mbox_read_reg);
		}

		spin_unlock_irqrestore(&mbox->lock, flags);
		octeon_mbox_process_cmd(mbox, &mbox_cmd);
		return 0;
	}

	spin_unlock_irqrestore(&mbox->lock, flags);
	WARN_ON(1);

	return 0;
}