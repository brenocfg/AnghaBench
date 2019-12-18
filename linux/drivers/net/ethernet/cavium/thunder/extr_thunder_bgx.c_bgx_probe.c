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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct bgx {int bgx_id; int max_lmac; int is_rgx; int is_dlm; scalar_t__ lmac_count; int /*<<< orphan*/  reg_base; struct pci_dev* pdev; } ;

/* Variables and functions */
 int BGX_ID_MASK ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_BGX_PER_CN81XX ; 
 int MAX_LMAC_PER_BGX ; 
 int /*<<< orphan*/  PCI_CFG_REG_BAR_NUM ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 scalar_t__ PCI_DEVICE_ID_THUNDER_RGX ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 scalar_t__ PCI_SUBSYS_DEVID_81XX_BGX ; 
 scalar_t__ PCI_SUBSYS_DEVID_83XX_BGX ; 
 int /*<<< orphan*/  bgx_get_qlm_mode (struct bgx*) ; 
 int /*<<< orphan*/  bgx_init_hw (struct bgx*) ; 
 int bgx_init_phy (struct bgx*) ; 
 int /*<<< orphan*/  bgx_lmac_disable (struct bgx*,scalar_t__) ; 
 int bgx_lmac_enable (struct bgx*,scalar_t__) ; 
 struct bgx** bgx_vnic ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct bgx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int max_bgx_per_node ; 
 int nic_get_node_id (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct bgx*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_max_bgx_per_node (struct pci_dev*) ; 
 int /*<<< orphan*/  xcv_init_hw () ; 

__attribute__((used)) static int bgx_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int err;
	struct device *dev = &pdev->dev;
	struct bgx *bgx = NULL;
	u8 lmac;
	u16 sdevid;

	bgx = devm_kzalloc(dev, sizeof(*bgx), GFP_KERNEL);
	if (!bgx)
		return -ENOMEM;
	bgx->pdev = pdev;

	pci_set_drvdata(pdev, bgx);

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, NULL);
		return err;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		goto err_disable_device;
	}

	/* MAP configuration registers */
	bgx->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	if (!bgx->reg_base) {
		dev_err(dev, "BGX: Cannot map CSR memory space, aborting\n");
		err = -ENOMEM;
		goto err_release_regions;
	}

	set_max_bgx_per_node(pdev);

	pci_read_config_word(pdev, PCI_DEVICE_ID, &sdevid);
	if (sdevid != PCI_DEVICE_ID_THUNDER_RGX) {
		bgx->bgx_id = (pci_resource_start(pdev,
			PCI_CFG_REG_BAR_NUM) >> 24) & BGX_ID_MASK;
		bgx->bgx_id += nic_get_node_id(pdev) * max_bgx_per_node;
		bgx->max_lmac = MAX_LMAC_PER_BGX;
		bgx_vnic[bgx->bgx_id] = bgx;
	} else {
		bgx->is_rgx = true;
		bgx->max_lmac = 1;
		bgx->bgx_id = MAX_BGX_PER_CN81XX - 1;
		bgx_vnic[bgx->bgx_id] = bgx;
		xcv_init_hw();
	}

	/* On 81xx all are DLMs and on 83xx there are 3 BGX QLMs and one
	 * BGX i.e BGX2 can be split across 2 DLMs.
	 */
	pci_read_config_word(pdev, PCI_SUBSYSTEM_ID, &sdevid);
	if ((sdevid == PCI_SUBSYS_DEVID_81XX_BGX) ||
	    ((sdevid == PCI_SUBSYS_DEVID_83XX_BGX) && (bgx->bgx_id == 2)))
		bgx->is_dlm = true;

	bgx_get_qlm_mode(bgx);

	err = bgx_init_phy(bgx);
	if (err)
		goto err_enable;

	bgx_init_hw(bgx);

	/* Enable all LMACs */
	for (lmac = 0; lmac < bgx->lmac_count; lmac++) {
		err = bgx_lmac_enable(bgx, lmac);
		if (err) {
			dev_err(dev, "BGX%d failed to enable lmac%d\n",
				bgx->bgx_id, lmac);
			while (lmac)
				bgx_lmac_disable(bgx, --lmac);
			goto err_enable;
		}
	}

	return 0;

err_enable:
	bgx_vnic[bgx->bgx_id] = NULL;
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
	return err;
}