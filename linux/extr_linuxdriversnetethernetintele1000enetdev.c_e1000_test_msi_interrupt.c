#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int flags; TYPE_1__* pdev; int /*<<< orphan*/  int_mode; struct e1000_hw hw; struct net_device* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000E_INT_MODE_LEGACY ; 
 int /*<<< orphan*/  E1000_ICS_RXSEQ ; 
 int FLAG_MSI_TEST_FAILED ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  ICS ; 
 int /*<<< orphan*/  e1000_free_irq (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_intr_msi_test ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int e1000_request_irq (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset_interrupt_capability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_set_interrupt_capability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  e_info (char*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int pci_enable_msi (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int e1000_test_msi_interrupt(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	int err;

	/* poll_enable hasn't been called yet, so don't need disable */
	/* clear any pending events */
	er32(ICR);

	/* free the real vector and request a test handler */
	e1000_free_irq(adapter);
	e1000e_reset_interrupt_capability(adapter);

	/* Assume that the test fails, if it succeeds then the test
	 * MSI irq handler will unset this flag
	 */
	adapter->flags |= FLAG_MSI_TEST_FAILED;

	err = pci_enable_msi(adapter->pdev);
	if (err)
		goto msi_test_failed;

	err = request_irq(adapter->pdev->irq, e1000_intr_msi_test, 0,
			  netdev->name, netdev);
	if (err) {
		pci_disable_msi(adapter->pdev);
		goto msi_test_failed;
	}

	/* Force memory writes to complete before enabling and firing an
	 * interrupt.
	 */
	wmb();

	e1000_irq_enable(adapter);

	/* fire an unusual interrupt on the test handler */
	ew32(ICS, E1000_ICS_RXSEQ);
	e1e_flush();
	msleep(100);

	e1000_irq_disable(adapter);

	rmb();			/* read flags after interrupt has been fired */

	if (adapter->flags & FLAG_MSI_TEST_FAILED) {
		adapter->int_mode = E1000E_INT_MODE_LEGACY;
		e_info("MSI interrupt test failed, using legacy interrupt.\n");
	} else {
		e_dbg("MSI interrupt test succeeded!\n");
	}

	free_irq(adapter->pdev->irq, netdev);
	pci_disable_msi(adapter->pdev);

msi_test_failed:
	e1000e_set_interrupt_capability(adapter);
	return e1000_request_irq(adapter);
}