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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct hl_device {int /*<<< orphan*/  dev; scalar_t__ pldm; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HL_PCI_ELBI_TIMEOUT_MSEC ; 
 scalar_t__ HL_PLDM_PCI_ELBI_TIMEOUT_MSEC ; 
 int PCI_CONFIG_ELBI_CTRL_WRITE ; 
 int PCI_CONFIG_ELBI_STS_DONE ; 
 int PCI_CONFIG_ELBI_STS_ERR ; 
 int PCI_CONFIG_ELBI_STS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmPCI_CONFIG_ELBI_ADDR ; 
 int /*<<< orphan*/  mmPCI_CONFIG_ELBI_CTRL ; 
 int /*<<< orphan*/  mmPCI_CONFIG_ELBI_DATA ; 
 int /*<<< orphan*/  mmPCI_CONFIG_ELBI_STS ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hl_pci_elbi_write(struct hl_device *hdev, u64 addr, u32 data)
{
	struct pci_dev *pdev = hdev->pdev;
	ktime_t timeout;
	u64 msec;
	u32 val;

	if (hdev->pldm)
		msec = HL_PLDM_PCI_ELBI_TIMEOUT_MSEC;
	else
		msec = HL_PCI_ELBI_TIMEOUT_MSEC;

	/* Clear previous status */
	pci_write_config_dword(pdev, mmPCI_CONFIG_ELBI_STS, 0);

	pci_write_config_dword(pdev, mmPCI_CONFIG_ELBI_ADDR, (u32) addr);
	pci_write_config_dword(pdev, mmPCI_CONFIG_ELBI_DATA, data);
	pci_write_config_dword(pdev, mmPCI_CONFIG_ELBI_CTRL,
				PCI_CONFIG_ELBI_CTRL_WRITE);

	timeout = ktime_add_ms(ktime_get(), msec);
	for (;;) {
		pci_read_config_dword(pdev, mmPCI_CONFIG_ELBI_STS, &val);
		if (val & PCI_CONFIG_ELBI_STS_MASK)
			break;
		if (ktime_compare(ktime_get(), timeout) > 0) {
			pci_read_config_dword(pdev, mmPCI_CONFIG_ELBI_STS,
						&val);
			break;
		}

		usleep_range(300, 500);
	}

	if ((val & PCI_CONFIG_ELBI_STS_MASK) == PCI_CONFIG_ELBI_STS_DONE)
		return 0;

	if (val & PCI_CONFIG_ELBI_STS_ERR) {
		dev_err(hdev->dev, "Error writing to ELBI\n");
		return -EIO;
	}

	if (!(val & PCI_CONFIG_ELBI_STS_MASK)) {
		dev_err(hdev->dev, "ELBI write didn't finish in time\n");
		return -EIO;
	}

	dev_err(hdev->dev, "ELBI write has undefined bits in status\n");
	return -EIO;
}