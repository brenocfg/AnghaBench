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
struct sky2_status_le {int dummy; } ;
struct sky2_hw {int ports; int flags; int st_size; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; int /*<<< orphan*/  st_dma; int /*<<< orphan*/  st_le; int /*<<< orphan*/  napi; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  watchdog_timer; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  CS_RST_SET ; 
 int SKY2_HW_USE_MSI ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sky2_hw*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sky2_hw*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sky2_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sky2_power_aux (struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_remove(struct pci_dev *pdev)
{
	struct sky2_hw *hw = pci_get_drvdata(pdev);
	int i;

	if (!hw)
		return;

	del_timer_sync(&hw->watchdog_timer);
	cancel_work_sync(&hw->restart_work);

	for (i = hw->ports-1; i >= 0; --i)
		unregister_netdev(hw->dev[i]);

	sky2_write32(hw, B0_IMSK, 0);
	sky2_read32(hw, B0_IMSK);

	sky2_power_aux(hw);

	sky2_write8(hw, B0_CTST, CS_RST_SET);
	sky2_read8(hw, B0_CTST);

	if (hw->ports > 1) {
		napi_disable(&hw->napi);
		free_irq(pdev->irq, hw);
	}

	if (hw->flags & SKY2_HW_USE_MSI)
		pci_disable_msi(pdev);
	pci_free_consistent(pdev, hw->st_size * sizeof(struct sky2_status_le),
			    hw->st_le, hw->st_dma);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	for (i = hw->ports-1; i >= 0; --i)
		free_netdev(hw->dev[i]);

	iounmap(hw->regs);
	kfree(hw);
}