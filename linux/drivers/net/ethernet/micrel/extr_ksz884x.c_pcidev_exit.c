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
struct TYPE_2__ {int dev_count; struct platform_info* ksz_switch; scalar_t__ io; } ;
struct dev_info {int /*<<< orphan*/  pdev; TYPE_1__ hw; } ;
struct platform_info {scalar_t__* netdev; struct dev_info dev_info; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct platform_info*) ; 
 int /*<<< orphan*/  ksz_free_mem (struct dev_info*) ; 
 int /*<<< orphan*/  netdev_free (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 struct platform_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcidev_exit(struct pci_dev *pdev)
{
	int i;
	struct platform_info *info = pci_get_drvdata(pdev);
	struct dev_info *hw_priv = &info->dev_info;

	release_mem_region(pci_resource_start(pdev, 0),
		pci_resource_len(pdev, 0));
	for (i = 0; i < hw_priv->hw.dev_count; i++) {
		if (info->netdev[i])
			netdev_free(info->netdev[i]);
	}
	if (hw_priv->hw.io)
		iounmap(hw_priv->hw.io);
	ksz_free_mem(hw_priv);
	kfree(hw_priv->hw.ksz_switch);
	pci_dev_put(hw_priv->pdev);
	kfree(info);
}