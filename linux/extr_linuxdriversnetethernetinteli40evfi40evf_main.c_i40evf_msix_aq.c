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
struct net_device {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {int /*<<< orphan*/  adminq_task; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFINT_ICR01 ; 
 int /*<<< orphan*/  I40E_VFINT_ICR0_ENA1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t i40evf_msix_aq(int irq, void *data)
{
	struct net_device *netdev = data;
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	struct i40e_hw *hw = &adapter->hw;

	/* handle non-queue interrupts, these reads clear the registers */
	rd32(hw, I40E_VFINT_ICR01);
	rd32(hw, I40E_VFINT_ICR0_ENA1);

	/* schedule work on the private workqueue */
	schedule_work(&adapter->adminq_task);

	return IRQ_HANDLED;
}