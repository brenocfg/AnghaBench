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
struct tsi721_device {void* odb_base; void* regs; TYPE_1__* p2r_bar; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;
struct TYPE_2__ {scalar_t__ size; void* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_0 ; 
 int /*<<< orphan*/  BAR_1 ; 
 int /*<<< orphan*/  BAR_2 ; 
 int /*<<< orphan*/  BAR_4 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_MEM_64 ; 
 int IORESOURCE_PREFETCH ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int PCI_EXP_DEVCTL2_COMP_TIMEOUT ; 
 int PCI_EXP_DEVCTL_NOSNOOP_EN ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int PCI_EXP_DEVCTL_RELAX_EN ; 
 int PCI_STD_RESOURCE_END ; 
 scalar_t__ TSI721_DB_WIN_SIZE ; 
 int TSI721_MSIXPBA_OFFSET ; 
 int TSI721_MSIXTBL_OFFSET ; 
 int /*<<< orphan*/  TSI721_PCIECFG_EPCTL ; 
 int /*<<< orphan*/  TSI721_PCIECFG_MSIXPBA ; 
 int /*<<< orphan*/  TSI721_PCIECFG_MSIXTBL ; 
 scalar_t__ TSI721_REG_SPACE_SIZE ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct tsi721_device*) ; 
 struct tsi721_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct tsi721_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int,int) ; 
 int pcie_mrrs ; 
 int /*<<< orphan*/  tsi721_bdma_maint_free (struct tsi721_device*) ; 
 scalar_t__ tsi721_bdma_maint_init (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_disable_ints (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_doorbell_free (struct tsi721_device*) ; 
 int tsi721_doorbell_init (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_init_pc2sr_mapping (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_init_sr2pc_mapping (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_interrupts_init (struct tsi721_device*) ; 
 int tsi721_messages_init (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_port_write_free (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_port_write_init (struct tsi721_device*) ; 
 int tsi721_setup_mport (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tsi_info (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int tsi721_probe(struct pci_dev *pdev,
				  const struct pci_device_id *id)
{
	struct tsi721_device *priv;
	int err;

	priv = kzalloc(sizeof(struct tsi721_device), GFP_KERNEL);
	if (!priv) {
		err = -ENOMEM;
		goto err_exit;
	}

	err = pci_enable_device(pdev);
	if (err) {
		tsi_err(&pdev->dev, "Failed to enable PCI device");
		goto err_clean;
	}

	priv->pdev = pdev;

#ifdef DEBUG
	{
		int i;

		for (i = 0; i <= PCI_STD_RESOURCE_END; i++) {
			tsi_debug(INIT, &pdev->dev, "res%d %pR",
				  i, &pdev->resource[i]);
		}
	}
#endif
	/*
	 * Verify BAR configuration
	 */

	/* BAR_0 (registers) must be 512KB+ in 32-bit address space */
	if (!(pci_resource_flags(pdev, BAR_0) & IORESOURCE_MEM) ||
	    pci_resource_flags(pdev, BAR_0) & IORESOURCE_MEM_64 ||
	    pci_resource_len(pdev, BAR_0) < TSI721_REG_SPACE_SIZE) {
		tsi_err(&pdev->dev, "Missing or misconfigured CSR BAR0");
		err = -ENODEV;
		goto err_disable_pdev;
	}

	/* BAR_1 (outbound doorbells) must be 16MB+ in 32-bit address space */
	if (!(pci_resource_flags(pdev, BAR_1) & IORESOURCE_MEM) ||
	    pci_resource_flags(pdev, BAR_1) & IORESOURCE_MEM_64 ||
	    pci_resource_len(pdev, BAR_1) < TSI721_DB_WIN_SIZE) {
		tsi_err(&pdev->dev, "Missing or misconfigured Doorbell BAR1");
		err = -ENODEV;
		goto err_disable_pdev;
	}

	/*
	 * BAR_2 and BAR_4 (outbound translation) must be in 64-bit PCIe address
	 * space.
	 * NOTE: BAR_2 and BAR_4 are not used by this version of driver.
	 * It may be a good idea to keep them disabled using HW configuration
	 * to save PCI memory space.
	 */

	priv->p2r_bar[0].size = priv->p2r_bar[1].size = 0;

	if (pci_resource_flags(pdev, BAR_2) & IORESOURCE_MEM_64) {
		if (pci_resource_flags(pdev, BAR_2) & IORESOURCE_PREFETCH)
			tsi_debug(INIT, &pdev->dev,
				 "Prefetchable OBW BAR2 will not be used");
		else {
			priv->p2r_bar[0].base = pci_resource_start(pdev, BAR_2);
			priv->p2r_bar[0].size = pci_resource_len(pdev, BAR_2);
		}
	}

	if (pci_resource_flags(pdev, BAR_4) & IORESOURCE_MEM_64) {
		if (pci_resource_flags(pdev, BAR_4) & IORESOURCE_PREFETCH)
			tsi_debug(INIT, &pdev->dev,
				 "Prefetchable OBW BAR4 will not be used");
		else {
			priv->p2r_bar[1].base = pci_resource_start(pdev, BAR_4);
			priv->p2r_bar[1].size = pci_resource_len(pdev, BAR_4);
		}
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		tsi_err(&pdev->dev, "Unable to obtain PCI resources");
		goto err_disable_pdev;
	}

	pci_set_master(pdev);

	priv->regs = pci_ioremap_bar(pdev, BAR_0);
	if (!priv->regs) {
		tsi_err(&pdev->dev, "Unable to map device registers space");
		err = -ENOMEM;
		goto err_free_res;
	}

	priv->odb_base = pci_ioremap_bar(pdev, BAR_1);
	if (!priv->odb_base) {
		tsi_err(&pdev->dev, "Unable to map outbound doorbells space");
		err = -ENOMEM;
		goto err_unmap_bars;
	}

	/* Configure DMA attributes. */
	if (pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err) {
			tsi_err(&pdev->dev, "Unable to set DMA mask");
			goto err_unmap_bars;
		}

		if (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32)))
			tsi_info(&pdev->dev, "Unable to set consistent DMA mask");
	} else {
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		if (err)
			tsi_info(&pdev->dev, "Unable to set consistent DMA mask");
	}

	BUG_ON(!pci_is_pcie(pdev));

	/* Clear "no snoop" and "relaxed ordering" bits. */
	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
		PCI_EXP_DEVCTL_RELAX_EN | PCI_EXP_DEVCTL_NOSNOOP_EN, 0);

	/* Override PCIe Maximum Read Request Size setting if requested */
	if (pcie_mrrs >= 0) {
		if (pcie_mrrs <= 5)
			pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
					PCI_EXP_DEVCTL_READRQ, pcie_mrrs << 12);
		else
			tsi_info(&pdev->dev,
				 "Invalid MRRS override value %d", pcie_mrrs);
	}

	/* Set PCIe completion timeout to 1-10ms */
	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL2,
					   PCI_EXP_DEVCTL2_COMP_TIMEOUT, 0x2);

	/*
	 * FIXUP: correct offsets of MSI-X tables in the MSI-X Capability Block
	 */
	pci_write_config_dword(pdev, TSI721_PCIECFG_EPCTL, 0x01);
	pci_write_config_dword(pdev, TSI721_PCIECFG_MSIXTBL,
						TSI721_MSIXTBL_OFFSET);
	pci_write_config_dword(pdev, TSI721_PCIECFG_MSIXPBA,
						TSI721_MSIXPBA_OFFSET);
	pci_write_config_dword(pdev, TSI721_PCIECFG_EPCTL, 0);
	/* End of FIXUP */

	tsi721_disable_ints(priv);

	tsi721_init_pc2sr_mapping(priv);
	tsi721_init_sr2pc_mapping(priv);

	if (tsi721_bdma_maint_init(priv)) {
		tsi_err(&pdev->dev, "BDMA initialization failed");
		err = -ENOMEM;
		goto err_unmap_bars;
	}

	err = tsi721_doorbell_init(priv);
	if (err)
		goto err_free_bdma;

	tsi721_port_write_init(priv);

	err = tsi721_messages_init(priv);
	if (err)
		goto err_free_consistent;

	err = tsi721_setup_mport(priv);
	if (err)
		goto err_free_consistent;

	pci_set_drvdata(pdev, priv);
	tsi721_interrupts_init(priv);

	return 0;

err_free_consistent:
	tsi721_port_write_free(priv);
	tsi721_doorbell_free(priv);
err_free_bdma:
	tsi721_bdma_maint_free(priv);
err_unmap_bars:
	if (priv->regs)
		iounmap(priv->regs);
	if (priv->odb_base)
		iounmap(priv->odb_base);
err_free_res:
	pci_release_regions(pdev);
	pci_clear_master(pdev);
err_disable_pdev:
	pci_disable_device(pdev);
err_clean:
	kfree(priv);
err_exit:
	return err;
}