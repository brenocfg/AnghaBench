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
struct wil6210_priv {int n_msi; int /*<<< orphan*/  mutex; struct pci_dev* pdev; } ;
struct pci_dev {int msi_enabled; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int n_msi ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 scalar_t__ pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  wil6210_fini_irq (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int wil6210_init_irq (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int wil_reset (struct wil6210_priv*,int) ; 

__attribute__((used)) static int wil_if_pcie_enable(struct wil6210_priv *wil)
{
	struct pci_dev *pdev = wil->pdev;
	int rc;
	/* on platforms with buggy ACPI, pdev->msi_enabled may be set to
	 * allow pci_enable_device to work. This indicates INTx was not routed
	 * and only MSI should be used
	 */
	int msi_only = pdev->msi_enabled;

	wil_dbg_misc(wil, "if_pcie_enable\n");

	pci_set_master(pdev);

	/* how many MSI interrupts to request? */
	switch (n_msi) {
	case 3:
	case 1:
		wil_dbg_misc(wil, "Setup %d MSI interrupts\n", n_msi);
		break;
	case 0:
		wil_dbg_misc(wil, "MSI interrupts disabled, use INTx\n");
		break;
	default:
		wil_err(wil, "Invalid n_msi=%d, default to 1\n", n_msi);
		n_msi = 1;
	}

	if (n_msi == 3 &&
	    pci_alloc_irq_vectors(pdev, n_msi, n_msi, PCI_IRQ_MSI) < n_msi) {
		wil_err(wil, "3 MSI mode failed, try 1 MSI\n");
		n_msi = 1;
	}

	if (n_msi == 1 && pci_enable_msi(pdev)) {
		wil_err(wil, "pci_enable_msi failed, use INTx\n");
		n_msi = 0;
	}

	wil->n_msi = n_msi;

	if (wil->n_msi == 0 && msi_only) {
		wil_err(wil, "Interrupt pin not routed, unable to use INTx\n");
		rc = -ENODEV;
		goto stop_master;
	}

	rc = wil6210_init_irq(wil, pdev->irq);
	if (rc)
		goto release_vectors;

	/* need reset here to obtain MAC */
	mutex_lock(&wil->mutex);
	rc = wil_reset(wil, false);
	mutex_unlock(&wil->mutex);
	if (rc)
		goto release_irq;

	return 0;

 release_irq:
	wil6210_fini_irq(wil, pdev->irq);
 release_vectors:
	/* safe to call if no allocation */
	pci_free_irq_vectors(pdev);
 stop_master:
	pci_clear_master(pdev);
	return rc;
}