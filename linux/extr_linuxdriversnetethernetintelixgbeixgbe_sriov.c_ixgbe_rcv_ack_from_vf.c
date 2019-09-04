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
typedef  size_t u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {TYPE_1__* vfinfo; struct ixgbe_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  clear_to_send; } ;

/* Variables and functions */
 size_t IXGBE_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  ixgbe_write_mbx (struct ixgbe_hw*,size_t*,int,size_t) ; 

__attribute__((used)) static void ixgbe_rcv_ack_from_vf(struct ixgbe_adapter *adapter, u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 msg = IXGBE_VT_MSGTYPE_NACK;

	/* if device isn't clear to send it shouldn't be reading either */
	if (!adapter->vfinfo[vf].clear_to_send)
		ixgbe_write_mbx(hw, &msg, 1, vf);
}