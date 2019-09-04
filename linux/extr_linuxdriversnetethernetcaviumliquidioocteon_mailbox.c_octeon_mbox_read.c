#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
union octeon_mbox_message {scalar_t__ u64; TYPE_1__ s; } ;
struct TYPE_12__ {int len; } ;
struct TYPE_13__ {scalar_t__ u64; TYPE_5__ s; } ;
struct TYPE_14__ {scalar_t__* data; int recv_len; TYPE_6__ msg; int /*<<< orphan*/  q_no; } ;
struct TYPE_9__ {int len; } ;
struct TYPE_10__ {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_11__ {scalar_t__* data; int recv_len; TYPE_3__ msg; int /*<<< orphan*/  q_no; } ;
struct octeon_mbox {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  mbox_read_reg; TYPE_7__ mbox_resp; TYPE_4__ mbox_req; int /*<<< orphan*/  q_no; } ;

/* Variables and functions */
 scalar_t__ OCTEON_MBOX_REQUEST ; 
 scalar_t__ OCTEON_MBOX_RESPONSE ; 
 int OCTEON_MBOX_STATE_ERROR ; 
 int OCTEON_MBOX_STATE_IDLE ; 
 int OCTEON_MBOX_STATE_REQUEST_RECEIVED ; 
 int OCTEON_MBOX_STATE_REQUEST_RECEIVING ; 
 int OCTEON_MBOX_STATE_RESPONSE_PENDING ; 
 int OCTEON_MBOX_STATE_RESPONSE_RECEIVED ; 
 int OCTEON_MBOX_STATE_RESPONSE_RECEIVING ; 
 scalar_t__ OCTEON_PFVFACK ; 
 scalar_t__ OCTEON_PFVFERR ; 
 scalar_t__ OCTEON_PFVFSIG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (scalar_t__,int /*<<< orphan*/ ) ; 

int octeon_mbox_read(struct octeon_mbox *mbox)
{
	union octeon_mbox_message msg;
	int ret = 0;

	spin_lock(&mbox->lock);

	msg.u64 = readq(mbox->mbox_read_reg);

	if ((msg.u64 == OCTEON_PFVFACK) || (msg.u64 == OCTEON_PFVFSIG)) {
		spin_unlock(&mbox->lock);
		return 0;
	}

	if (mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVING) {
		mbox->mbox_req.data[mbox->mbox_req.recv_len - 1] = msg.u64;
		mbox->mbox_req.recv_len++;
	} else {
		if (mbox->state & OCTEON_MBOX_STATE_RESPONSE_RECEIVING) {
			mbox->mbox_resp.data[mbox->mbox_resp.recv_len - 1] =
				msg.u64;
			mbox->mbox_resp.recv_len++;
		} else {
			if ((mbox->state & OCTEON_MBOX_STATE_IDLE) &&
			    (msg.s.type == OCTEON_MBOX_REQUEST)) {
				mbox->state &= ~OCTEON_MBOX_STATE_IDLE;
				mbox->state |=
				    OCTEON_MBOX_STATE_REQUEST_RECEIVING;
				mbox->mbox_req.msg.u64 = msg.u64;
				mbox->mbox_req.q_no = mbox->q_no;
				mbox->mbox_req.recv_len = 1;
			} else {
				if ((mbox->state &
				     OCTEON_MBOX_STATE_RESPONSE_PENDING) &&
				    (msg.s.type == OCTEON_MBOX_RESPONSE)) {
					mbox->state &=
					    ~OCTEON_MBOX_STATE_RESPONSE_PENDING;
					mbox->state |=
					    OCTEON_MBOX_STATE_RESPONSE_RECEIVING
					    ;
					mbox->mbox_resp.msg.u64 = msg.u64;
					mbox->mbox_resp.q_no = mbox->q_no;
					mbox->mbox_resp.recv_len = 1;
				} else {
					writeq(OCTEON_PFVFERR,
					       mbox->mbox_read_reg);
					mbox->state |= OCTEON_MBOX_STATE_ERROR;
					spin_unlock(&mbox->lock);
					return 1;
				}
			}
		}
	}

	if (mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVING) {
		if (mbox->mbox_req.recv_len < mbox->mbox_req.msg.s.len) {
			ret = 0;
		} else {
			mbox->state &= ~OCTEON_MBOX_STATE_REQUEST_RECEIVING;
			mbox->state |= OCTEON_MBOX_STATE_REQUEST_RECEIVED;
			ret = 1;
		}
	} else {
		if (mbox->state & OCTEON_MBOX_STATE_RESPONSE_RECEIVING) {
			if (mbox->mbox_resp.recv_len <
			    mbox->mbox_resp.msg.s.len) {
				ret = 0;
			} else {
				mbox->state &=
				    ~OCTEON_MBOX_STATE_RESPONSE_RECEIVING;
				mbox->state |=
				    OCTEON_MBOX_STATE_RESPONSE_RECEIVED;
				ret = 1;
			}
		} else {
			WARN_ON(1);
		}
	}

	writeq(OCTEON_PFVFACK, mbox->mbox_read_reg);

	spin_unlock(&mbox->lock);

	return ret;
}