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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct netxen_adapter {size_t fw_type; int /*<<< orphan*/ * fw; struct pci_dev* pdev; } ;

/* Variables and functions */
 size_t NX_FLASH_ROMIMAGE ; 
 size_t NX_UNKNOWN_ROMIMAGE ; 
 int /*<<< orphan*/ * fw_name ; 
 int /*<<< orphan*/  msleep (int) ; 
 int netxen_validate_firmware (struct netxen_adapter*) ; 
 int /*<<< orphan*/  nx_get_next_fwtype (struct netxen_adapter*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void netxen_request_firmware(struct netxen_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	int rc = 0;

	adapter->fw_type = NX_UNKNOWN_ROMIMAGE;

next:
	nx_get_next_fwtype(adapter);

	if (adapter->fw_type == NX_FLASH_ROMIMAGE) {
		adapter->fw = NULL;
	} else {
		rc = request_firmware(&adapter->fw,
				fw_name[adapter->fw_type], &pdev->dev);
		if (rc != 0)
			goto next;

		rc = netxen_validate_firmware(adapter);
		if (rc != 0) {
			release_firmware(adapter->fw);
			msleep(1);
			goto next;
		}
	}
}