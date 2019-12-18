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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  flags; TYPE_1__* netdev; struct e1000_hw hw; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL_CFIEN ; 
 int /*<<< orphan*/  E1000_RCTL_VFE ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __e1000_vlan_mode (struct e1000_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_update_mng_vlan (struct e1000_adapter*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_vlan_filter_on_off(struct e1000_adapter *adapter,
				     bool filter_on)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);

	__e1000_vlan_mode(adapter, adapter->netdev->features);
	if (filter_on) {
		/* enable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~E1000_RCTL_CFIEN;
		if (!(adapter->netdev->flags & IFF_PROMISC))
			rctl |= E1000_RCTL_VFE;
		ew32(RCTL, rctl);
		e1000_update_mng_vlan(adapter);
	} else {
		/* disable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~E1000_RCTL_VFE;
		ew32(RCTL, rctl);
	}

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);
}