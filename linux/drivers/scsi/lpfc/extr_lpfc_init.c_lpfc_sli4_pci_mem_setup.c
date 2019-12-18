#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  word0; } ;
struct TYPE_3__ {void* conf_regs_memmap_p; void* ctrl_regs_memmap_p; void* drbl_regs_memmap_p; int /*<<< orphan*/  sli4_write_cq_db; int /*<<< orphan*/  sli4_write_eq_db; int /*<<< orphan*/  sli4_eq_clr_intr; void* dpp_regs_memmap_p; TYPE_2__ sli_intf; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; void* pci_bar4_memmap_p; void* pci_bar2_map; void* pci_bar2_memmap_p; void* pci_bar1_map; void* pci_bar0_map; void* pci_bar0_memmap_p; struct pci_dev* pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_SLI_INTF ; 
#define  LPFC_SLI_INTF_IF_TYPE_0 130 
#define  LPFC_SLI_INTF_IF_TYPE_2 129 
#define  LPFC_SLI_INTF_IF_TYPE_6 128 
 scalar_t__ LPFC_SLI_INTF_VALID ; 
 int /*<<< orphan*/  LPFC_VF0 ; 
 int PCI_64BIT_BAR0 ; 
 int PCI_64BIT_BAR2 ; 
 int PCI_64BIT_BAR4 ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ioremap (void*,unsigned long) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_bar0_register_memmap (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_sli4_bar1_register_memmap (struct lpfc_hba*,int) ; 
 int lpfc_sli4_bar2_register_memmap (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_eq_clr_intr ; 
 int /*<<< orphan*/  lpfc_sli4_if6_eq_clr_intr ; 
 int /*<<< orphan*/  lpfc_sli4_if6_write_cq_db ; 
 int /*<<< orphan*/  lpfc_sli4_if6_write_eq_db ; 
 int /*<<< orphan*/  lpfc_sli4_write_cq_db ; 
 int /*<<< orphan*/  lpfc_sli4_write_eq_db ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_sli_intf_valid ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int
lpfc_sli4_pci_mem_setup(struct lpfc_hba *phba)
{
	struct pci_dev *pdev = phba->pcidev;
	unsigned long bar0map_len, bar1map_len, bar2map_len;
	int error;
	uint32_t if_type;

	if (!pdev)
		return -ENODEV;

	/* Set the device DMA mask size */
	error = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (error)
		error = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (error)
		return error;

	/*
	 * The BARs and register set definitions and offset locations are
	 * dependent on the if_type.
	 */
	if (pci_read_config_dword(pdev, LPFC_SLI_INTF,
				  &phba->sli4_hba.sli_intf.word0)) {
		return -ENODEV;
	}

	/* There is no SLI3 failback for SLI4 devices. */
	if (bf_get(lpfc_sli_intf_valid, &phba->sli4_hba.sli_intf) !=
	    LPFC_SLI_INTF_VALID) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2894 SLI_INTF reg contents invalid "
				"sli_intf reg 0x%x\n",
				phba->sli4_hba.sli_intf.word0);
		return -ENODEV;
	}

	if_type = bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf);
	/*
	 * Get the bus address of SLI4 device Bar regions and the
	 * number of bytes required by each mapping. The mapping of the
	 * particular PCI BARs regions is dependent on the type of
	 * SLI4 device.
	 */
	if (pci_resource_start(pdev, PCI_64BIT_BAR0)) {
		phba->pci_bar0_map = pci_resource_start(pdev, PCI_64BIT_BAR0);
		bar0map_len = pci_resource_len(pdev, PCI_64BIT_BAR0);

		/*
		 * Map SLI4 PCI Config Space Register base to a kernel virtual
		 * addr
		 */
		phba->sli4_hba.conf_regs_memmap_p =
			ioremap(phba->pci_bar0_map, bar0map_len);
		if (!phba->sli4_hba.conf_regs_memmap_p) {
			dev_printk(KERN_ERR, &pdev->dev,
				   "ioremap failed for SLI4 PCI config "
				   "registers.\n");
			return -ENODEV;
		}
		phba->pci_bar0_memmap_p = phba->sli4_hba.conf_regs_memmap_p;
		/* Set up BAR0 PCI config space register memory map */
		lpfc_sli4_bar0_register_memmap(phba, if_type);
	} else {
		phba->pci_bar0_map = pci_resource_start(pdev, 1);
		bar0map_len = pci_resource_len(pdev, 1);
		if (if_type >= LPFC_SLI_INTF_IF_TYPE_2) {
			dev_printk(KERN_ERR, &pdev->dev,
			   "FATAL - No BAR0 mapping for SLI4, if_type 2\n");
			return -ENODEV;
		}
		phba->sli4_hba.conf_regs_memmap_p =
				ioremap(phba->pci_bar0_map, bar0map_len);
		if (!phba->sli4_hba.conf_regs_memmap_p) {
			dev_printk(KERN_ERR, &pdev->dev,
				"ioremap failed for SLI4 PCI config "
				"registers.\n");
			return -ENODEV;
		}
		lpfc_sli4_bar0_register_memmap(phba, if_type);
	}

	if (if_type == LPFC_SLI_INTF_IF_TYPE_0) {
		if (pci_resource_start(pdev, PCI_64BIT_BAR2)) {
			/*
			 * Map SLI4 if type 0 HBA Control Register base to a
			 * kernel virtual address and setup the registers.
			 */
			phba->pci_bar1_map = pci_resource_start(pdev,
								PCI_64BIT_BAR2);
			bar1map_len = pci_resource_len(pdev, PCI_64BIT_BAR2);
			phba->sli4_hba.ctrl_regs_memmap_p =
					ioremap(phba->pci_bar1_map,
						bar1map_len);
			if (!phba->sli4_hba.ctrl_regs_memmap_p) {
				dev_err(&pdev->dev,
					   "ioremap failed for SLI4 HBA "
					    "control registers.\n");
				error = -ENOMEM;
				goto out_iounmap_conf;
			}
			phba->pci_bar2_memmap_p =
					 phba->sli4_hba.ctrl_regs_memmap_p;
			lpfc_sli4_bar1_register_memmap(phba, if_type);
		} else {
			error = -ENOMEM;
			goto out_iounmap_conf;
		}
	}

	if ((if_type == LPFC_SLI_INTF_IF_TYPE_6) &&
	    (pci_resource_start(pdev, PCI_64BIT_BAR2))) {
		/*
		 * Map SLI4 if type 6 HBA Doorbell Register base to a kernel
		 * virtual address and setup the registers.
		 */
		phba->pci_bar1_map = pci_resource_start(pdev, PCI_64BIT_BAR2);
		bar1map_len = pci_resource_len(pdev, PCI_64BIT_BAR2);
		phba->sli4_hba.drbl_regs_memmap_p =
				ioremap(phba->pci_bar1_map, bar1map_len);
		if (!phba->sli4_hba.drbl_regs_memmap_p) {
			dev_err(&pdev->dev,
			   "ioremap failed for SLI4 HBA doorbell registers.\n");
			error = -ENOMEM;
			goto out_iounmap_conf;
		}
		phba->pci_bar2_memmap_p = phba->sli4_hba.drbl_regs_memmap_p;
		lpfc_sli4_bar1_register_memmap(phba, if_type);
	}

	if (if_type == LPFC_SLI_INTF_IF_TYPE_0) {
		if (pci_resource_start(pdev, PCI_64BIT_BAR4)) {
			/*
			 * Map SLI4 if type 0 HBA Doorbell Register base to
			 * a kernel virtual address and setup the registers.
			 */
			phba->pci_bar2_map = pci_resource_start(pdev,
								PCI_64BIT_BAR4);
			bar2map_len = pci_resource_len(pdev, PCI_64BIT_BAR4);
			phba->sli4_hba.drbl_regs_memmap_p =
					ioremap(phba->pci_bar2_map,
						bar2map_len);
			if (!phba->sli4_hba.drbl_regs_memmap_p) {
				dev_err(&pdev->dev,
					   "ioremap failed for SLI4 HBA"
					   " doorbell registers.\n");
				error = -ENOMEM;
				goto out_iounmap_ctrl;
			}
			phba->pci_bar4_memmap_p =
					phba->sli4_hba.drbl_regs_memmap_p;
			error = lpfc_sli4_bar2_register_memmap(phba, LPFC_VF0);
			if (error)
				goto out_iounmap_all;
		} else {
			error = -ENOMEM;
			goto out_iounmap_all;
		}
	}

	if (if_type == LPFC_SLI_INTF_IF_TYPE_6 &&
	    pci_resource_start(pdev, PCI_64BIT_BAR4)) {
		/*
		 * Map SLI4 if type 6 HBA DPP Register base to a kernel
		 * virtual address and setup the registers.
		 */
		phba->pci_bar2_map = pci_resource_start(pdev, PCI_64BIT_BAR4);
		bar2map_len = pci_resource_len(pdev, PCI_64BIT_BAR4);
		phba->sli4_hba.dpp_regs_memmap_p =
				ioremap(phba->pci_bar2_map, bar2map_len);
		if (!phba->sli4_hba.dpp_regs_memmap_p) {
			dev_err(&pdev->dev,
			   "ioremap failed for SLI4 HBA dpp registers.\n");
			error = -ENOMEM;
			goto out_iounmap_ctrl;
		}
		phba->pci_bar4_memmap_p = phba->sli4_hba.dpp_regs_memmap_p;
	}

	/* Set up the EQ/CQ register handeling functions now */
	switch (if_type) {
	case LPFC_SLI_INTF_IF_TYPE_0:
	case LPFC_SLI_INTF_IF_TYPE_2:
		phba->sli4_hba.sli4_eq_clr_intr = lpfc_sli4_eq_clr_intr;
		phba->sli4_hba.sli4_write_eq_db = lpfc_sli4_write_eq_db;
		phba->sli4_hba.sli4_write_cq_db = lpfc_sli4_write_cq_db;
		break;
	case LPFC_SLI_INTF_IF_TYPE_6:
		phba->sli4_hba.sli4_eq_clr_intr = lpfc_sli4_if6_eq_clr_intr;
		phba->sli4_hba.sli4_write_eq_db = lpfc_sli4_if6_write_eq_db;
		phba->sli4_hba.sli4_write_cq_db = lpfc_sli4_if6_write_cq_db;
		break;
	default:
		break;
	}

	return 0;

out_iounmap_all:
	iounmap(phba->sli4_hba.drbl_regs_memmap_p);
out_iounmap_ctrl:
	iounmap(phba->sli4_hba.ctrl_regs_memmap_p);
out_iounmap_conf:
	iounmap(phba->sli4_hba.conf_regs_memmap_p);

	return error;
}