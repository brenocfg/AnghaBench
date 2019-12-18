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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  sli_flag; } ;
struct lpfc_hba {int cfg_sli_mode; int cfg_aer_support; int hba_flag; int sli_rev; int sli3_options; int max_vpi; int* vpi_ids; int /*<<< orphan*/  link_state; int /*<<< orphan*/  hbalock; TYPE_1__ sli; int /*<<< orphan*/ * vpi_bmask; int /*<<< orphan*/  iocb_rsp_size; int /*<<< orphan*/  iocb_cmd_size; int /*<<< orphan*/  pcidev; scalar_t__ fcp_embed_io; int /*<<< orphan*/  cfg_enable_npiv; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HBA_AER_ENABLED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_INIT ; 
 int LOG_VPORT ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_PROCESS_LA ; 
 int LPFC_SLI3_HBQ_ENABLED ; 
 int LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  SLI2_IOCB_CMD_SIZE ; 
 int /*<<< orphan*/  SLI2_IOCB_RSP_SIZE ; 
 int /*<<< orphan*/  SLI3_IOCB_CMD_SIZE ; 
 int /*<<< orphan*/  SLI3_IOCB_RSP_SIZE ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int lpfc_config_port_post (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 int lpfc_sli_config_port (struct lpfc_hba*,int) ; 
 int lpfc_sli_hbq_setup (struct lpfc_hba*) ; 
 int lpfc_sli_ring_map (struct lpfc_hba*) ; 
 int pci_enable_pcie_error_reporting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_sli_hba_setup(struct lpfc_hba *phba)
{
	uint32_t rc;
	int  mode = 3, i;
	int longs;

	switch (phba->cfg_sli_mode) {
	case 2:
		if (phba->cfg_enable_npiv) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT | LOG_VPORT,
				"1824 NPIV enabled: Override sli_mode "
				"parameter (%d) to auto (0).\n",
				phba->cfg_sli_mode);
			break;
		}
		mode = 2;
		break;
	case 0:
	case 3:
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT | LOG_VPORT,
				"1819 Unrecognized sli_mode parameter: %d.\n",
				phba->cfg_sli_mode);

		break;
	}
	phba->fcp_embed_io = 0;	/* SLI4 FC support only */

	rc = lpfc_sli_config_port(phba, mode);

	if (rc && phba->cfg_sli_mode == 3)
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT | LOG_VPORT,
				"1820 Unable to select SLI-3.  "
				"Not supported by adapter.\n");
	if (rc && mode != 2)
		rc = lpfc_sli_config_port(phba, 2);
	else if (rc && mode == 2)
		rc = lpfc_sli_config_port(phba, 3);
	if (rc)
		goto lpfc_sli_hba_setup_error;

	/* Enable PCIe device Advanced Error Reporting (AER) if configured */
	if (phba->cfg_aer_support == 1 && !(phba->hba_flag & HBA_AER_ENABLED)) {
		rc = pci_enable_pcie_error_reporting(phba->pcidev);
		if (!rc) {
			lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
					"2709 This device supports "
					"Advanced Error Reporting (AER)\n");
			spin_lock_irq(&phba->hbalock);
			phba->hba_flag |= HBA_AER_ENABLED;
			spin_unlock_irq(&phba->hbalock);
		} else {
			lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
					"2708 This device does not support "
					"Advanced Error Reporting (AER): %d\n",
					rc);
			phba->cfg_aer_support = 0;
		}
	}

	if (phba->sli_rev == 3) {
		phba->iocb_cmd_size = SLI3_IOCB_CMD_SIZE;
		phba->iocb_rsp_size = SLI3_IOCB_RSP_SIZE;
	} else {
		phba->iocb_cmd_size = SLI2_IOCB_CMD_SIZE;
		phba->iocb_rsp_size = SLI2_IOCB_RSP_SIZE;
		phba->sli3_options = 0;
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"0444 Firmware in SLI %x mode. Max_vpi %d\n",
			phba->sli_rev, phba->max_vpi);
	rc = lpfc_sli_ring_map(phba);

	if (rc)
		goto lpfc_sli_hba_setup_error;

	/* Initialize VPIs. */
	if (phba->sli_rev == LPFC_SLI_REV3) {
		/*
		 * The VPI bitmask and physical ID array are allocated
		 * and initialized once only - at driver load.  A port
		 * reset doesn't need to reinitialize this memory.
		 */
		if ((phba->vpi_bmask == NULL) && (phba->vpi_ids == NULL)) {
			longs = (phba->max_vpi + BITS_PER_LONG) / BITS_PER_LONG;
			phba->vpi_bmask = kcalloc(longs,
						  sizeof(unsigned long),
						  GFP_KERNEL);
			if (!phba->vpi_bmask) {
				rc = -ENOMEM;
				goto lpfc_sli_hba_setup_error;
			}

			phba->vpi_ids = kcalloc(phba->max_vpi + 1,
						sizeof(uint16_t),
						GFP_KERNEL);
			if (!phba->vpi_ids) {
				kfree(phba->vpi_bmask);
				rc = -ENOMEM;
				goto lpfc_sli_hba_setup_error;
			}
			for (i = 0; i < phba->max_vpi; i++)
				phba->vpi_ids[i] = i;
		}
	}

	/* Init HBQs */
	if (phba->sli3_options & LPFC_SLI3_HBQ_ENABLED) {
		rc = lpfc_sli_hbq_setup(phba);
		if (rc)
			goto lpfc_sli_hba_setup_error;
	}
	spin_lock_irq(&phba->hbalock);
	phba->sli.sli_flag |= LPFC_PROCESS_LA;
	spin_unlock_irq(&phba->hbalock);

	rc = lpfc_config_port_post(phba);
	if (rc)
		goto lpfc_sli_hba_setup_error;

	return rc;

lpfc_sli_hba_setup_error:
	phba->link_state = LPFC_HBA_ERROR;
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"0445 Firmware initialization failed\n");
	return rc;
}