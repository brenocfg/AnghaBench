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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct cas_init_block {int dummy; } ;
struct cas {int /*<<< orphan*/  regs; int /*<<< orphan*/  block_dvma; int /*<<< orphan*/  init_block; scalar_t__ orig_cacheline_size; int /*<<< orphan*/  pm_mutex; scalar_t__ hw_running; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  fw_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cas_shutdown (struct cas*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cas_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct cas *cp;
	if (!dev)
		return;

	cp = netdev_priv(dev);
	unregister_netdev(dev);

	vfree(cp->fw_data);

	mutex_lock(&cp->pm_mutex);
	cancel_work_sync(&cp->reset_task);
	if (cp->hw_running)
		cas_shutdown(cp);
	mutex_unlock(&cp->pm_mutex);

#if 1
	if (cp->orig_cacheline_size) {
		/* Restore the cache line size if we had modified
		 * it.
		 */
		pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE,
				      cp->orig_cacheline_size);
	}
#endif
	pci_free_consistent(pdev, sizeof(struct cas_init_block),
			    cp->init_block, cp->block_dvma);
	pci_iounmap(pdev, cp->regs);
	free_netdev(dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}