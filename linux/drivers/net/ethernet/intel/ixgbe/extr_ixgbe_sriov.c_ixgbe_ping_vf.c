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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {TYPE_1__* vfinfo; struct ixgbe_hw hw; } ;
struct TYPE_2__ {scalar_t__ clear_to_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PF_CONTROL_MSG ; 
 int /*<<< orphan*/  IXGBE_VT_MSGTYPE_CTS ; 
 int /*<<< orphan*/  ixgbe_write_mbx (struct ixgbe_hw*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void ixgbe_ping_vf(struct ixgbe_adapter *adapter, int vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 ping;

	ping = IXGBE_PF_CONTROL_MSG;
	if (adapter->vfinfo[vf].clear_to_send)
		ping |= IXGBE_VT_MSGTYPE_CTS;
	ixgbe_write_mbx(hw, &ping, 1, vf);
}