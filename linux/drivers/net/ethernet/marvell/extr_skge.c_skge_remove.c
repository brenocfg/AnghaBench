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
struct skge_hw {int ports; int /*<<< orphan*/  regs; int /*<<< orphan*/  hw_lock; scalar_t__ intr_mask; int /*<<< orphan*/  phy_task; struct net_device** dev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B0_LED ; 
 int /*<<< orphan*/  CS_RST_SET ; 
 int /*<<< orphan*/  LED_STAT_OFF ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct skge_hw*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct skge_hw*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct skge_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write16 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void skge_remove(struct pci_dev *pdev)
{
	struct skge_hw *hw  = pci_get_drvdata(pdev);
	struct net_device *dev0, *dev1;

	if (!hw)
		return;

	dev1 = hw->dev[1];
	if (dev1)
		unregister_netdev(dev1);
	dev0 = hw->dev[0];
	unregister_netdev(dev0);

	tasklet_kill(&hw->phy_task);

	spin_lock_irq(&hw->hw_lock);
	hw->intr_mask = 0;

	if (hw->ports > 1) {
		skge_write32(hw, B0_IMSK, 0);
		skge_read32(hw, B0_IMSK);
	}
	spin_unlock_irq(&hw->hw_lock);

	skge_write16(hw, B0_LED, LED_STAT_OFF);
	skge_write8(hw, B0_CTST, CS_RST_SET);

	if (hw->ports > 1)
		free_irq(pdev->irq, hw);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	if (dev1)
		free_netdev(dev1);
	free_netdev(dev0);

	iounmap(hw->regs);
	kfree(hw);
}