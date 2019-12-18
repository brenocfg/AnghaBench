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
struct pci_device_id {int dummy; } ;
struct pci_dev {int device; int /*<<< orphan*/  dev; } ;
struct nforce2_smbus {int blockops; int can_abort; int /*<<< orphan*/  adapter; scalar_t__ base; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFORCE_PCI_SMB1 ; 
 int /*<<< orphan*/  NFORCE_PCI_SMB2 ; 
#define  PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS 130 
#define  PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SMBUS 129 
#define  PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SMBUS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 struct nforce2_smbus* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nforce2_smbus*) ; 
 int /*<<< orphan*/  nforce2_dmi_blacklist2 ; 
 int nforce2_probe_smb (struct pci_dev*,int,int /*<<< orphan*/ ,struct nforce2_smbus*,char*) ; 
 int /*<<< orphan*/  nforce2_set_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct nforce2_smbus*) ; 

__attribute__((used)) static int nforce2_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct nforce2_smbus *smbuses;
	int res1, res2;

	/* we support 2 SMBus adapters */
	smbuses = kcalloc(2, sizeof(struct nforce2_smbus), GFP_KERNEL);
	if (!smbuses)
		return -ENOMEM;
	pci_set_drvdata(dev, smbuses);

	switch (dev->device) {
	case PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS:
	case PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SMBUS:
	case PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SMBUS:
		smbuses[0].blockops = 1;
		smbuses[1].blockops = 1;
		smbuses[0].can_abort = 1;
		smbuses[1].can_abort = 1;
	}

	/* SMBus adapter 1 */
	res1 = nforce2_probe_smb(dev, 4, NFORCE_PCI_SMB1, &smbuses[0], "SMB1");
	if (res1 < 0)
		smbuses[0].base = 0;	/* to have a check value */

	/* SMBus adapter 2 */
	if (dmi_check_system(nforce2_dmi_blacklist2)) {
		dev_err(&dev->dev, "Disabling SMB2 for safety reasons.\n");
		res2 = -EPERM;
		smbuses[1].base = 0;
	} else {
		res2 = nforce2_probe_smb(dev, 5, NFORCE_PCI_SMB2, &smbuses[1],
					 "SMB2");
		if (res2 < 0)
			smbuses[1].base = 0;	/* to have a check value */
	}

	if ((res1 < 0) && (res2 < 0)) {
		/* we did not find even one of the SMBuses, so we give up */
		kfree(smbuses);
		return -ENODEV;
	}

	nforce2_set_reference(&smbuses[0].adapter);
	return 0;
}