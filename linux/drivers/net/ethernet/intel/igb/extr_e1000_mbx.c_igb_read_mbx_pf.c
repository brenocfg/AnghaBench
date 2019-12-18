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
struct TYPE_4__ {int /*<<< orphan*/  msgs_rx; } ;
struct TYPE_3__ {TYPE_2__ stats; } ;
struct e1000_hw {TYPE_1__ mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_P2VMAILBOX (size_t) ; 
 int E1000_P2VMAILBOX_ACK ; 
 int E1000_P2VMAILBOX_PFU ; 
 int /*<<< orphan*/  E1000_VMBMEM (size_t) ; 
 int /*<<< orphan*/  array_rd32 (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ igb_obtain_mbx_lock_pf (struct e1000_hw*,size_t) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_read_mbx_pf(struct e1000_hw *hw, u32 *msg, u16 size,
			   u16 vf_number, bool unlock)
{
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = igb_obtain_mbx_lock_pf(hw, vf_number);
	if (ret_val)
		goto out_no_read;

	/* copy the message to the mailbox memory buffer */
	for (i = 0; i < size; i++)
		msg[i] = array_rd32(E1000_VMBMEM(vf_number), i);

	/* Acknowledge the message and release mailbox lock (or not) */
	if (unlock)
		wr32(E1000_P2VMAILBOX(vf_number), E1000_P2VMAILBOX_ACK);
	else
		wr32(E1000_P2VMAILBOX(vf_number),
		     E1000_P2VMAILBOX_ACK | E1000_P2VMAILBOX_PFU);

	/* update stats */
	hw->mbx.stats.msgs_rx++;

out_no_read:
	return ret_val;
}