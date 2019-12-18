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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct brcmf_pciedev_info* pcie; } ;
struct brcmf_pciedev_info {scalar_t__ settings; scalar_t__ ci; struct brcmf_pciedev_info* msgbuf; struct brcmf_pciedev_info* flowrings; TYPE_1__ bus_priv; int /*<<< orphan*/  state; struct brcmf_pciedev_info* devinfo; } ;
struct brcmf_bus {scalar_t__ settings; scalar_t__ ci; struct brcmf_bus* msgbuf; struct brcmf_bus* flowrings; TYPE_1__ bus_priv; int /*<<< orphan*/  state; struct brcmf_bus* devinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMFMAC_PCIE_STATE_DOWN ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_chip_detach (scalar_t__) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_pcie_intr_disable (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_irq (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_resource (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_ringbuffers (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_scratchbuffers (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_reset_device (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_release_module_param (scalar_t__) ; 
 struct brcmf_pciedev_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct brcmf_pciedev_info*) ; 

__attribute__((used)) static void
brcmf_pcie_remove(struct pci_dev *pdev)
{
	struct brcmf_pciedev_info *devinfo;
	struct brcmf_bus *bus;

	brcmf_dbg(PCIE, "Enter\n");

	bus = dev_get_drvdata(&pdev->dev);
	if (bus == NULL)
		return;

	devinfo = bus->bus_priv.pcie->devinfo;

	devinfo->state = BRCMFMAC_PCIE_STATE_DOWN;
	if (devinfo->ci)
		brcmf_pcie_intr_disable(devinfo);

	brcmf_detach(&pdev->dev);
	brcmf_free(&pdev->dev);

	kfree(bus->bus_priv.pcie);
	kfree(bus->msgbuf->flowrings);
	kfree(bus->msgbuf);
	kfree(bus);

	brcmf_pcie_release_irq(devinfo);
	brcmf_pcie_release_scratchbuffers(devinfo);
	brcmf_pcie_release_ringbuffers(devinfo);
	brcmf_pcie_reset_device(devinfo);
	brcmf_pcie_release_resource(devinfo);

	if (devinfo->ci)
		brcmf_chip_detach(devinfo->ci);
	if (devinfo->settings)
		brcmf_release_module_param(devinfo->settings);

	kfree(devinfo);
	dev_set_drvdata(&pdev->dev, NULL);
}