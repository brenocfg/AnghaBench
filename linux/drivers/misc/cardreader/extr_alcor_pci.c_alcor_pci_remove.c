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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct alcor_pci_priv {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  alcor_pci_aspm_ctrl (struct alcor_pci_priv*,int) ; 
 int /*<<< orphan*/  alcor_pci_idr ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct alcor_pci_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alcor_pci_remove(struct pci_dev *pdev)
{
	struct alcor_pci_priv *priv;

	priv = pci_get_drvdata(pdev);

	alcor_pci_aspm_ctrl(priv, 1);

	mfd_remove_devices(&pdev->dev);

	ida_simple_remove(&alcor_pci_idr, priv->id);

	pci_release_regions(pdev);
	pci_set_drvdata(pdev, NULL);
}