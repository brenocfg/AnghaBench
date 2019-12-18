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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASMT_CONTROL_REG ; 
 int /*<<< orphan*/  ASMT_CONTROL_WRITE_BIT ; 
 int /*<<< orphan*/  ASMT_DATA_WRITE0_REG ; 
 int /*<<< orphan*/  ASMT_DATA_WRITE1_REG ; 
 int /*<<< orphan*/  ASMT_FLOWCTL_ADDR ; 
 int /*<<< orphan*/  ASMT_FLOWCTL_DATA ; 
 int /*<<< orphan*/  ASMT_PSEUDO_DATA ; 
 int /*<<< orphan*/  ASMT_WRITEREG_CMD ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_asmedia_wait_write (struct pci_dev*) ; 

void usb_asmedia_modifyflowcontrol(struct pci_dev *pdev)
{
	if (usb_asmedia_wait_write(pdev) != 0)
		return;

	/* send command and address to device */
	pci_write_config_dword(pdev, ASMT_DATA_WRITE0_REG, ASMT_WRITEREG_CMD);
	pci_write_config_dword(pdev, ASMT_DATA_WRITE1_REG, ASMT_FLOWCTL_ADDR);
	pci_write_config_byte(pdev, ASMT_CONTROL_REG, ASMT_CONTROL_WRITE_BIT);

	if (usb_asmedia_wait_write(pdev) != 0)
		return;

	/* send data to device */
	pci_write_config_dword(pdev, ASMT_DATA_WRITE0_REG, ASMT_FLOWCTL_DATA);
	pci_write_config_dword(pdev, ASMT_DATA_WRITE1_REG, ASMT_PSEUDO_DATA);
	pci_write_config_byte(pdev, ASMT_CONTROL_REG, ASMT_CONTROL_WRITE_BIT);
}