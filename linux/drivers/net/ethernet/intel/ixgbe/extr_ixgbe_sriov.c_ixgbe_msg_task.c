#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {scalar_t__ num_vfs; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_check_for_ack (struct ixgbe_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_check_for_msg (struct ixgbe_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_check_for_rst (struct ixgbe_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_rcv_ack_from_vf (struct ixgbe_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_rcv_msg_from_vf (struct ixgbe_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_vf_reset_event (struct ixgbe_adapter*,scalar_t__) ; 

void ixgbe_msg_task(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 vf;

	for (vf = 0; vf < adapter->num_vfs; vf++) {
		/* process any reset requests */
		if (!ixgbe_check_for_rst(hw, vf))
			ixgbe_vf_reset_event(adapter, vf);

		/* process any messages pending */
		if (!ixgbe_check_for_msg(hw, vf))
			ixgbe_rcv_msg_from_vf(adapter, vf);

		/* process any acks */
		if (!ixgbe_check_for_ack(hw, vf))
			ixgbe_rcv_ack_from_vf(adapter, vf);
	}
}