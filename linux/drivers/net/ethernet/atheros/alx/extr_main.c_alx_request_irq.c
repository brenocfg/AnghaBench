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
typedef  int u32 ;
struct pci_dev {scalar_t__ msi_enabled; scalar_t__ msix_enabled; } ;
struct alx_hw {int imt; struct pci_dev* pdev; } ;
struct alx_priv {TYPE_1__* dev; struct alx_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ALX_MSI_MASK_SEL_LINE ; 
 int /*<<< orphan*/  ALX_MSI_RETRANS_TIMER ; 
 int ALX_MSI_RETRANS_TM_SHIFT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  alx_config_vector_mapping (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_intr_legacy ; 
 int /*<<< orphan*/  alx_intr_msi ; 
 int alx_realloc_resources (struct alx_priv*) ; 
 int alx_request_msix (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct alx_priv*) ; 

__attribute__((used)) static int alx_request_irq(struct alx_priv *alx)
{
	struct pci_dev *pdev = alx->hw.pdev;
	struct alx_hw *hw = &alx->hw;
	int err;
	u32 msi_ctrl;

	msi_ctrl = (hw->imt >> 1) << ALX_MSI_RETRANS_TM_SHIFT;

	if (alx->hw.pdev->msix_enabled) {
		alx_write_mem32(hw, ALX_MSI_RETRANS_TIMER, msi_ctrl);
		err = alx_request_msix(alx);
		if (!err)
			goto out;

		/* msix request failed, realloc resources */
		err = alx_realloc_resources(alx);
		if (err)
			goto out;
	}

	if (alx->hw.pdev->msi_enabled) {
		alx_write_mem32(hw, ALX_MSI_RETRANS_TIMER,
				msi_ctrl | ALX_MSI_MASK_SEL_LINE);
		err = request_irq(pci_irq_vector(pdev, 0), alx_intr_msi, 0,
				  alx->dev->name, alx);
		if (!err)
			goto out;

		/* fall back to legacy interrupt */
		pci_free_irq_vectors(alx->hw.pdev);
	}

	alx_write_mem32(hw, ALX_MSI_RETRANS_TIMER, 0);
	err = request_irq(pci_irq_vector(pdev, 0), alx_intr_legacy, IRQF_SHARED,
			  alx->dev->name, alx);
out:
	if (!err)
		alx_config_vector_mapping(alx);
	else
		netdev_err(alx->dev, "IRQ registration failed!\n");
	return err;
}