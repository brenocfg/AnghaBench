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
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMCP_PACKET_DISABLE_PCI_ACCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hl_fw_send_pci_access_msg (struct hl_device*,int /*<<< orphan*/ ) ; 

int goya_suspend(struct hl_device *hdev)
{
	int rc;

	rc = hl_fw_send_pci_access_msg(hdev, ARMCP_PACKET_DISABLE_PCI_ACCESS);
	if (rc)
		dev_err(hdev->dev, "Failed to disable PCI access from CPU\n");

	return rc;
}