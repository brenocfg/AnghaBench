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
struct xgbe_prv_data {int /*<<< orphan*/  pcidev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  xgbe_deconfig_netdev (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_free_pdata (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_pci_remove(struct pci_dev *pdev)
{
	struct xgbe_prv_data *pdata = pci_get_drvdata(pdev);

	xgbe_deconfig_netdev(pdata);

	pci_free_irq_vectors(pdata->pcidev);

	xgbe_free_pdata(pdata);
}