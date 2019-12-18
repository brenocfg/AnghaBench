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
struct rocker {int /*<<< orphan*/  pdev; int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  rocker_owq; int /*<<< orphan*/  fib_nb; } ;
struct pci_dev {int dummy; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  ROCKER_CONTROL_RESET ; 
 int /*<<< orphan*/  ROCKER_MSIX_VEC_CMD ; 
 int /*<<< orphan*/  ROCKER_MSIX_VEC_EVENT ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rocker*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rocker*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 struct rocker* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_dma_rings_fini (struct rocker*) ; 
 int /*<<< orphan*/  rocker_msix_fini (struct rocker*) ; 
 int /*<<< orphan*/  rocker_msix_vector (struct rocker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_remove_ports (struct rocker*) ; 
 struct notifier_block rocker_switchdev_blocking_notifier ; 
 int /*<<< orphan*/  rocker_switchdev_notifier ; 
 int /*<<< orphan*/  rocker_write32 (struct rocker*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_fib_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switchdev_blocking_notifier (struct notifier_block*) ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rocker_remove(struct pci_dev *pdev)
{
	struct rocker *rocker = pci_get_drvdata(pdev);
	struct notifier_block *nb;

	nb = &rocker_switchdev_blocking_notifier;
	unregister_switchdev_blocking_notifier(nb);

	unregister_switchdev_notifier(&rocker_switchdev_notifier);
	unregister_fib_notifier(&rocker->fib_nb);
	rocker_remove_ports(rocker);
	rocker_write32(rocker, CONTROL, ROCKER_CONTROL_RESET);
	destroy_workqueue(rocker->rocker_owq);
	free_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_EVENT), rocker);
	free_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_CMD), rocker);
	rocker_dma_rings_fini(rocker);
	rocker_msix_fini(rocker);
	iounmap(rocker->hw_addr);
	pci_release_regions(rocker->pdev);
	pci_disable_device(rocker->pdev);
	kfree(rocker);
}