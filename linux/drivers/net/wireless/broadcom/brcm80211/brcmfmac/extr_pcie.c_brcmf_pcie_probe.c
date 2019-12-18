#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct brcmf_pciedev_info* pcie; } ;
struct brcmf_pciedev_info {scalar_t__ settings; TYPE_2__* ci; struct brcmf_pciedev_info* msgbuf; int /*<<< orphan*/ * dev; struct pci_dev* pdev; int /*<<< orphan*/  wowl_supported; int /*<<< orphan*/  coreid; int /*<<< orphan*/  chip; int /*<<< orphan*/  proto_type; int /*<<< orphan*/ * ops; TYPE_1__ bus_priv; struct brcmf_pciedev_info* bus; struct brcmf_pciedev_info* devinfo; } ;
struct brcmf_pciedev {scalar_t__ settings; TYPE_2__* ci; struct brcmf_pciedev* msgbuf; int /*<<< orphan*/ * dev; struct pci_dev* pdev; int /*<<< orphan*/  wowl_supported; int /*<<< orphan*/  coreid; int /*<<< orphan*/  chip; int /*<<< orphan*/  proto_type; int /*<<< orphan*/ * ops; TYPE_1__ bus_priv; struct brcmf_pciedev* bus; struct brcmf_pciedev* devinfo; } ;
struct brcmf_fw_request {scalar_t__ settings; TYPE_2__* ci; struct brcmf_fw_request* msgbuf; int /*<<< orphan*/ * dev; struct pci_dev* pdev; int /*<<< orphan*/  wowl_supported; int /*<<< orphan*/  coreid; int /*<<< orphan*/  chip; int /*<<< orphan*/  proto_type; int /*<<< orphan*/ * ops; TYPE_1__ bus_priv; struct brcmf_fw_request* bus; struct brcmf_fw_request* devinfo; } ;
struct brcmf_bus {scalar_t__ settings; TYPE_2__* ci; struct brcmf_bus* msgbuf; int /*<<< orphan*/ * dev; struct pci_dev* pdev; int /*<<< orphan*/  wowl_supported; int /*<<< orphan*/  coreid; int /*<<< orphan*/  chip; int /*<<< orphan*/  proto_type; int /*<<< orphan*/ * ops; TYPE_1__ bus_priv; struct brcmf_bus* bus; struct brcmf_bus* devinfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BUSTYPE_PCIE ; 
 int /*<<< orphan*/  BRCMF_PROTO_MSGBUF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int PTR_ERR (TYPE_2__*) ; 
 int brcmf_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* brcmf_chip_attach (struct brcmf_pciedev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_chip_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_fw_get_firmwares (int /*<<< orphan*/ *,struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_get_module_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_bus_ops ; 
 int /*<<< orphan*/  brcmf_pcie_buscore_ops ; 
 struct brcmf_pciedev_info* brcmf_pcie_prepare_fw_request (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_resource (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_setup ; 
 int /*<<< orphan*/  brcmf_release_module_param (scalar_t__) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_pciedev_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pme_capable (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
brcmf_pcie_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int ret;
	struct brcmf_fw_request *fwreq;
	struct brcmf_pciedev_info *devinfo;
	struct brcmf_pciedev *pcie_bus_dev;
	struct brcmf_bus *bus;

	brcmf_dbg(PCIE, "Enter %x:%x\n", pdev->vendor, pdev->device);

	ret = -ENOMEM;
	devinfo = kzalloc(sizeof(*devinfo), GFP_KERNEL);
	if (devinfo == NULL)
		return ret;

	devinfo->pdev = pdev;
	pcie_bus_dev = NULL;
	devinfo->ci = brcmf_chip_attach(devinfo, &brcmf_pcie_buscore_ops);
	if (IS_ERR(devinfo->ci)) {
		ret = PTR_ERR(devinfo->ci);
		devinfo->ci = NULL;
		goto fail;
	}

	pcie_bus_dev = kzalloc(sizeof(*pcie_bus_dev), GFP_KERNEL);
	if (pcie_bus_dev == NULL) {
		ret = -ENOMEM;
		goto fail;
	}

	devinfo->settings = brcmf_get_module_param(&devinfo->pdev->dev,
						   BRCMF_BUSTYPE_PCIE,
						   devinfo->ci->chip,
						   devinfo->ci->chiprev);
	if (!devinfo->settings) {
		ret = -ENOMEM;
		goto fail;
	}

	bus = kzalloc(sizeof(*bus), GFP_KERNEL);
	if (!bus) {
		ret = -ENOMEM;
		goto fail;
	}
	bus->msgbuf = kzalloc(sizeof(*bus->msgbuf), GFP_KERNEL);
	if (!bus->msgbuf) {
		ret = -ENOMEM;
		kfree(bus);
		goto fail;
	}

	/* hook it all together. */
	pcie_bus_dev->devinfo = devinfo;
	pcie_bus_dev->bus = bus;
	bus->dev = &pdev->dev;
	bus->bus_priv.pcie = pcie_bus_dev;
	bus->ops = &brcmf_pcie_bus_ops;
	bus->proto_type = BRCMF_PROTO_MSGBUF;
	bus->chip = devinfo->coreid;
	bus->wowl_supported = pci_pme_capable(pdev, PCI_D3hot);
	dev_set_drvdata(&pdev->dev, bus);

	ret = brcmf_alloc(&devinfo->pdev->dev, devinfo->settings);
	if (ret)
		goto fail_bus;

	fwreq = brcmf_pcie_prepare_fw_request(devinfo);
	if (!fwreq) {
		ret = -ENOMEM;
		goto fail_bus;
	}

	ret = brcmf_fw_get_firmwares(bus->dev, fwreq, brcmf_pcie_setup);
	if (ret < 0) {
		kfree(fwreq);
		goto fail_bus;
	}
	return 0;

fail_bus:
	kfree(bus->msgbuf);
	kfree(bus);
fail:
	brcmf_err(NULL, "failed %x:%x\n", pdev->vendor, pdev->device);
	brcmf_pcie_release_resource(devinfo);
	if (devinfo->ci)
		brcmf_chip_detach(devinfo->ci);
	if (devinfo->settings)
		brcmf_release_module_param(devinfo->settings);
	kfree(pcie_bus_dev);
	kfree(devinfo);
	return ret;
}