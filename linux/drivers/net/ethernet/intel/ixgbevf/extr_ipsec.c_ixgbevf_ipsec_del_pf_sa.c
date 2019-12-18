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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int (* write_posted ) (struct ixgbe_hw*,scalar_t__*,int) ;int (* read_posted ) (struct ixgbe_hw*,scalar_t__*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mbx; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  mbx_lock; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  msgbuf ;

/* Variables and functions */
 scalar_t__ IXGBE_VF_IPSEC_DEL ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ixgbe_hw*,scalar_t__*,int) ; 
 int stub2 (struct ixgbe_hw*,scalar_t__*,int) ; 

__attribute__((used)) static int ixgbevf_ipsec_del_pf_sa(struct ixgbevf_adapter *adapter, int pfsa)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 msgbuf[2];
	int err;

	memset(msgbuf, 0, sizeof(msgbuf));
	msgbuf[0] = IXGBE_VF_IPSEC_DEL;
	msgbuf[1] = (u32)pfsa;

	spin_lock_bh(&adapter->mbx_lock);

	err = hw->mbx.ops.write_posted(hw, msgbuf, 2);
	if (err)
		goto out;

	err = hw->mbx.ops.read_posted(hw, msgbuf, 2);
	if (err)
		goto out;

out:
	spin_unlock_bh(&adapter->mbx_lock);
	return err;
}