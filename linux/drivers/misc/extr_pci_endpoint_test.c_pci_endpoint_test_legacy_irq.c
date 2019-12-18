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
typedef  int /*<<< orphan*/  u32 ;
struct pci_endpoint_test {int /*<<< orphan*/  irq_raised; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_RAISE_LEGACY_IRQ ; 
 int /*<<< orphan*/  IRQ_TYPE_LEGACY ; 
 int /*<<< orphan*/  PCI_ENDPOINT_TEST_COMMAND ; 
 int /*<<< orphan*/  PCI_ENDPOINT_TEST_IRQ_NUMBER ; 
 int /*<<< orphan*/  PCI_ENDPOINT_TEST_IRQ_TYPE ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pci_endpoint_test_writel (struct pci_endpoint_test*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pci_endpoint_test_legacy_irq(struct pci_endpoint_test *test)
{
	u32 val;

	pci_endpoint_test_writel(test, PCI_ENDPOINT_TEST_IRQ_TYPE,
				 IRQ_TYPE_LEGACY);
	pci_endpoint_test_writel(test, PCI_ENDPOINT_TEST_IRQ_NUMBER, 0);
	pci_endpoint_test_writel(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_RAISE_LEGACY_IRQ);
	val = wait_for_completion_timeout(&test->irq_raised,
					  msecs_to_jiffies(1000));
	if (!val)
		return false;

	return true;
}