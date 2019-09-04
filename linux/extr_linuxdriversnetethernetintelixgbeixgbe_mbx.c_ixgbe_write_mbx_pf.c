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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_3__ {int /*<<< orphan*/  msgs_tx; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct ixgbe_hw {TYPE_2__ mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PFMAILBOX (size_t) ; 
 int /*<<< orphan*/  IXGBE_PFMAILBOX_STS ; 
 int /*<<< orphan*/  IXGBE_PFMBMEM (size_t) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_for_ack_pf (struct ixgbe_hw*,size_t) ; 
 int /*<<< orphan*/  ixgbe_check_for_msg_pf (struct ixgbe_hw*,size_t) ; 
 scalar_t__ ixgbe_obtain_mbx_lock_pf (struct ixgbe_hw*,size_t) ; 

__attribute__((used)) static s32 ixgbe_write_mbx_pf(struct ixgbe_hw *hw, u32 *msg, u16 size,
			      u16 vf_number)
{
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = ixgbe_obtain_mbx_lock_pf(hw, vf_number);
	if (ret_val)
		return ret_val;

	/* flush msg and acks as we are overwriting the message buffer */
	ixgbe_check_for_msg_pf(hw, vf_number);
	ixgbe_check_for_ack_pf(hw, vf_number);

	/* copy the caller specified message to the mailbox memory buffer */
	for (i = 0; i < size; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_PFMBMEM(vf_number), i, msg[i]);

	/* Interrupt VF to tell it a message has been sent and release buffer*/
	IXGBE_WRITE_REG(hw, IXGBE_PFMAILBOX(vf_number), IXGBE_PFMAILBOX_STS);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

	return 0;
}