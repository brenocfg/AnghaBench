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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_tci; } ;
struct igc_nfc_filter {int action; TYPE_1__ filter; } ;
struct igc_hw {int dummy; } ;
struct igc_adapter {TYPE_2__* pdev; struct igc_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IGC_VLAPQF ; 
 int IGC_VLAPQF_P_VALID (int) ; 
 int IGC_VLAPQF_QUEUE_MASK ; 
 int IGC_VLAPQF_QUEUE_SEL (int,int) ; 
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igc_rxnfc_write_vlan_prio_filter(struct igc_adapter *adapter,
					    struct igc_nfc_filter *input)
{
	struct igc_hw *hw = &adapter->hw;
	u8 vlan_priority;
	u16 queue_index;
	u32 vlapqf;

	vlapqf = rd32(IGC_VLAPQF);
	vlan_priority = (ntohs(input->filter.vlan_tci) & VLAN_PRIO_MASK)
				>> VLAN_PRIO_SHIFT;
	queue_index = (vlapqf >> (vlan_priority * 4)) & IGC_VLAPQF_QUEUE_MASK;

	/* check whether this vlan prio is already set */
	if (vlapqf & IGC_VLAPQF_P_VALID(vlan_priority) &&
	    queue_index != input->action) {
		dev_err(&adapter->pdev->dev, "ethtool rxnfc set vlan prio filter failed.\n");
		return -EEXIST;
	}

	vlapqf |= IGC_VLAPQF_P_VALID(vlan_priority);
	vlapqf |= IGC_VLAPQF_QUEUE_SEL(vlan_priority, input->action);

	wr32(IGC_VLAPQF, vlapqf);

	return 0;
}