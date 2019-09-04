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
struct TYPE_2__ {scalar_t__ rsts; scalar_t__ acks; scalar_t__ reqs; scalar_t__ msgs_rx; scalar_t__ msgs_tx; } ;
struct ixgbe_mbx_info {TYPE_1__ stats; int /*<<< orphan*/  size; int /*<<< orphan*/  udelay; scalar_t__ timeout; } ;
struct ixgbe_hw {struct ixgbe_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VFMAILBOX_SIZE ; 
 int /*<<< orphan*/  IXGBE_VF_MBX_INIT_DELAY ; 

__attribute__((used)) static s32 ixgbevf_init_mbx_params_vf(struct ixgbe_hw *hw)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;

	/* start mailbox as timed out and let the reset_hw call set the timeout
	 * value to begin communications
	 */
	mbx->timeout = 0;
	mbx->udelay = IXGBE_VF_MBX_INIT_DELAY;

	mbx->size = IXGBE_VFMAILBOX_SIZE;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_rx = 0;
	mbx->stats.reqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.rsts = 0;

	return 0;
}