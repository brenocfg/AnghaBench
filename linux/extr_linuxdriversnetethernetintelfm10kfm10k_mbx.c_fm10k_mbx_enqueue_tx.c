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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* process ) (struct fm10k_hw*,struct fm10k_mbx_info*) ;} ;
struct fm10k_mbx_info {int state; TYPE_1__ ops; int /*<<< orphan*/  tail_len; int /*<<< orphan*/  tx_busy; scalar_t__ timeout; int /*<<< orphan*/  tx; int /*<<< orphan*/  udelay; } ;
struct fm10k_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_MBX_ERR_NO_MBX ; 
#define  FM10K_STATE_CLOSED 129 
#define  FM10K_STATE_DISCONNECT 128 
 scalar_t__ fm10k_fifo_enqueue (int /*<<< orphan*/ *,scalar_t__ const*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 fm10k_mbx_enqueue_tx(struct fm10k_hw *hw,
				struct fm10k_mbx_info *mbx, const u32 *msg)
{
	u32 countdown = mbx->timeout;
	s32 err;

	switch (mbx->state) {
	case FM10K_STATE_CLOSED:
	case FM10K_STATE_DISCONNECT:
		return FM10K_MBX_ERR_NO_MBX;
	default:
		break;
	}

	/* enqueue the message on the Tx FIFO */
	err = fm10k_fifo_enqueue(&mbx->tx, msg);

	/* if it failed give the FIFO a chance to drain */
	while (err && countdown) {
		countdown--;
		udelay(mbx->udelay);
		mbx->ops.process(hw, mbx);
		err = fm10k_fifo_enqueue(&mbx->tx, msg);
	}

	/* if we failed treat the error */
	if (err) {
		mbx->timeout = 0;
		mbx->tx_busy++;
	}

	/* begin processing message, ignore errors as this is just meant
	 * to start the mailbox flow so we are not concerned if there
	 * is a bad error, or the mailbox is already busy with a request
	 */
	if (!mbx->tail_len)
		mbx->ops.process(hw, mbx);

	return 0;
}