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
struct e1000_hw {int /*<<< orphan*/  mbx_lock; } ;
struct igbvf_adapter {int max_frame_size; struct e1000_hw hw; } ;

/* Variables and functions */
 int VLAN_TAG_SIZE ; 
 int /*<<< orphan*/  e1000_rlpml_set_vf (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igbvf_set_rlpml(struct igbvf_adapter *adapter)
{
	int max_frame_size;
	struct e1000_hw *hw = &adapter->hw;

	max_frame_size = adapter->max_frame_size + VLAN_TAG_SIZE;

	spin_lock_bh(&hw->mbx_lock);

	e1000_rlpml_set_vf(hw, max_frame_size);

	spin_unlock_bh(&hw->mbx_lock);
}