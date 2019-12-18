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
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  (* check_for_link ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {int /*<<< orphan*/  mbx_lock; TYPE_2__ mac; } ;
struct igbvf_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  STATUS ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static int igbvf_link_test(struct igbvf_adapter *adapter, u64 *data)
{
	struct e1000_hw *hw = &adapter->hw;
	*data = 0;

	spin_lock_bh(&hw->mbx_lock);

	hw->mac.ops.check_for_link(hw);

	spin_unlock_bh(&hw->mbx_lock);

	if (!(er32(STATUS) & E1000_STATUS_LU))
		*data = 1;

	return *data;
}