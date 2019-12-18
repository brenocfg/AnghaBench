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
struct iavf_hw {int dummy; } ;
struct iavf_adapter {int /*<<< orphan*/  adminq_task; struct iavf_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_VFINT_ICR01 ; 
 int /*<<< orphan*/  IAVF_VFINT_ICR0_ENA1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iavf_wq ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rd32 (struct iavf_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t iavf_msix_aq(int irq, void *data)
{
	struct net_device *netdev = data;
	struct iavf_adapter *adapter = netdev_priv(netdev);
	struct iavf_hw *hw = &adapter->hw;

	/* handle non-queue interrupts, these reads clear the registers */
	rd32(hw, IAVF_VFINT_ICR01);
	rd32(hw, IAVF_VFINT_ICR0_ENA1);

	/* schedule work on the private workqueue */
	queue_work(iavf_wq, &adapter->adminq_task);

	return IRQ_HANDLED;
}