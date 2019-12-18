#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {int num_phys; struct asd_sas_port** sas_port; struct asd_sas_phy** sas_phy; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  lldd_module; struct device* dev; int /*<<< orphan*/  sas_ha_name; struct hisi_hba* lldd_ha; TYPE_1__ core; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct hisi_hba {int n_phy; int prot_mask; TYPE_4__* hw; int /*<<< orphan*/  shost; TYPE_3__* port; TYPE_2__* phy; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  regs; } ;
struct asd_sas_port {int dummy; } ;
struct asd_sas_phy {int dummy; } ;
struct Scsi_Host {int max_channel; int max_cmd_len; void* cmd_per_lun; void* can_queue; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_id; int /*<<< orphan*/  transportt; } ;
struct TYPE_8__ {int (* hw_init ) (struct hisi_hba*) ;} ;
struct TYPE_7__ {struct asd_sas_port sas_port; } ;
struct TYPE_6__ {struct asd_sas_phy sas_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HISI_SAS_DIX_PROT_MASK ; 
 int /*<<< orphan*/  HISI_SAS_MAX_DEVICES ; 
 void* HISI_SAS_UNRESERVED_IPTT ; 
 int /*<<< orphan*/  SHOST_DIX_GUARD_CRC ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sas_ha_struct*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ hisi_sas_debugfs_enable ; 
 int /*<<< orphan*/  hisi_sas_debugfs_init (struct hisi_hba*) ; 
 struct Scsi_Host* hisi_sas_shost_alloc_pci (struct pci_dev*) ; 
 int /*<<< orphan*/  hisi_sas_stt ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prot_mask ; 
 int sas_register_ha (struct sas_ha_struct*) ; 
 int scsi_add_host (struct Scsi_Host*,struct device*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_set_guard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_set_prot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 struct hisi_hba* shost_priv (struct Scsi_Host*) ; 
 int stub1 (struct hisi_hba*) ; 

__attribute__((used)) static int
hisi_sas_v3_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct Scsi_Host *shost;
	struct hisi_hba *hisi_hba;
	struct device *dev = &pdev->dev;
	struct asd_sas_phy **arr_phy;
	struct asd_sas_port **arr_port;
	struct sas_ha_struct *sha;
	int rc, phy_nr, port_nr, i;

	rc = pci_enable_device(pdev);
	if (rc)
		goto err_out;

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, DRV_NAME);
	if (rc)
		goto err_out_disable_device;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (rc)
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (rc) {
		dev_err(dev, "No usable DMA addressing method\n");
		rc = -ENODEV;
		goto err_out_regions;
	}

	shost = hisi_sas_shost_alloc_pci(pdev);
	if (!shost) {
		rc = -ENOMEM;
		goto err_out_regions;
	}

	sha = SHOST_TO_SAS_HA(shost);
	hisi_hba = shost_priv(shost);
	dev_set_drvdata(dev, sha);

	hisi_hba->regs = pcim_iomap(pdev, 5, 0);
	if (!hisi_hba->regs) {
		dev_err(dev, "cannot map register\n");
		rc = -ENOMEM;
		goto err_out_ha;
	}

	phy_nr = port_nr = hisi_hba->n_phy;

	arr_phy = devm_kcalloc(dev, phy_nr, sizeof(void *), GFP_KERNEL);
	arr_port = devm_kcalloc(dev, port_nr, sizeof(void *), GFP_KERNEL);
	if (!arr_phy || !arr_port) {
		rc = -ENOMEM;
		goto err_out_ha;
	}

	sha->sas_phy = arr_phy;
	sha->sas_port = arr_port;
	sha->core.shost = shost;
	sha->lldd_ha = hisi_hba;

	shost->transportt = hisi_sas_stt;
	shost->max_id = HISI_SAS_MAX_DEVICES;
	shost->max_lun = ~0;
	shost->max_channel = 1;
	shost->max_cmd_len = 16;
	shost->can_queue = HISI_SAS_UNRESERVED_IPTT;
	shost->cmd_per_lun = HISI_SAS_UNRESERVED_IPTT;

	sha->sas_ha_name = DRV_NAME;
	sha->dev = dev;
	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &hisi_hba->sas_addr[0];
	sha->num_phys = hisi_hba->n_phy;

	for (i = 0; i < hisi_hba->n_phy; i++) {
		sha->sas_phy[i] = &hisi_hba->phy[i].sas_phy;
		sha->sas_port[i] = &hisi_hba->port[i].sas_port;
	}

	if (hisi_hba->prot_mask) {
		dev_info(dev, "Registering for DIF/DIX prot_mask=0x%x\n",
			 prot_mask);
		scsi_host_set_prot(hisi_hba->shost, prot_mask);
		if (hisi_hba->prot_mask & HISI_SAS_DIX_PROT_MASK)
			scsi_host_set_guard(hisi_hba->shost,
					    SHOST_DIX_GUARD_CRC);
	}

	if (hisi_sas_debugfs_enable)
		hisi_sas_debugfs_init(hisi_hba);

	rc = scsi_add_host(shost, dev);
	if (rc)
		goto err_out_ha;

	rc = sas_register_ha(sha);
	if (rc)
		goto err_out_register_ha;

	rc = hisi_hba->hw->hw_init(hisi_hba);
	if (rc)
		goto err_out_register_ha;

	scsi_scan_host(shost);

	return 0;

err_out_register_ha:
	scsi_remove_host(shost);
err_out_ha:
	scsi_host_put(shost);
err_out_regions:
	pci_release_regions(pdev);
err_out_disable_device:
	pci_disable_device(pdev);
err_out:
	return rc;
}