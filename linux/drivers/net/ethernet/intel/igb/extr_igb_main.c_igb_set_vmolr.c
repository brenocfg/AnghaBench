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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int rss_queues; int vfs_allocated_count; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VMOLR (int) ; 
 int E1000_VMOLR_AUPE ; 
 int E1000_VMOLR_BAM ; 
 int E1000_VMOLR_RSSE ; 
 scalar_t__ e1000_82576 ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void igb_set_vmolr(struct igb_adapter *adapter,
				 int vfn, bool aupe)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 vmolr;

	/* This register exists only on 82576 and newer so if we are older then
	 * we should exit and do nothing
	 */
	if (hw->mac.type < e1000_82576)
		return;

	vmolr = rd32(E1000_VMOLR(vfn));
	if (aupe)
		vmolr |= E1000_VMOLR_AUPE; /* Accept untagged packets */
	else
		vmolr &= ~(E1000_VMOLR_AUPE); /* Tagged packets ONLY */

	/* clear all bits that might not be set */
	vmolr &= ~(E1000_VMOLR_BAM | E1000_VMOLR_RSSE);

	if (adapter->rss_queues > 1 && vfn == adapter->vfs_allocated_count)
		vmolr |= E1000_VMOLR_RSSE; /* enable RSS */
	/* for VMDq only allow the VFs and pool 0 to accept broadcast and
	 * multicast packets
	 */
	if (vfn <= adapter->vfs_allocated_count)
		vmolr |= E1000_VMOLR_BAM; /* Accept broadcast */

	wr32(E1000_VMOLR(vfn), vmolr);
}