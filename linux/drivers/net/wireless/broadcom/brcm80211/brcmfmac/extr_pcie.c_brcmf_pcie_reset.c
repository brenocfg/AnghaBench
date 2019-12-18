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
struct device {int dummy; } ;
struct brcmf_pciedev_info {int dummy; } ;
struct brcmf_pciedev {struct brcmf_pciedev_info* devinfo; } ;
struct brcmf_fw_request {int dummy; } ;
struct TYPE_2__ {struct brcmf_pciedev* pcie; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  brcmf_detach (struct device*) ; 
 int brcmf_fw_get_firmwares (struct device*,struct brcmf_fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_bus_console_read (struct brcmf_pciedev_info*,int) ; 
 struct brcmf_fw_request* brcmf_pcie_prepare_fw_request (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_irq (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_ringbuffers (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_scratchbuffers (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_reset_device (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_setup ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw_request*) ; 

__attribute__((used)) static int brcmf_pcie_reset(struct device *dev)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_pciedev *buspub = bus_if->bus_priv.pcie;
	struct brcmf_pciedev_info *devinfo = buspub->devinfo;
	struct brcmf_fw_request *fwreq;
	int err;

	brcmf_pcie_bus_console_read(devinfo, true);

	brcmf_detach(dev);

	brcmf_pcie_release_irq(devinfo);
	brcmf_pcie_release_scratchbuffers(devinfo);
	brcmf_pcie_release_ringbuffers(devinfo);
	brcmf_pcie_reset_device(devinfo);

	fwreq = brcmf_pcie_prepare_fw_request(devinfo);
	if (!fwreq) {
		dev_err(dev, "Failed to prepare FW request\n");
		return -ENOMEM;
	}

	err = brcmf_fw_get_firmwares(dev, fwreq, brcmf_pcie_setup);
	if (err) {
		dev_err(dev, "Failed to prepare FW request\n");
		kfree(fwreq);
	}

	return err;
}