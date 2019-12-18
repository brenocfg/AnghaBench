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
typedef  int u16 ;
struct __vxge_hw_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __vxge_hw_device_pci_e_init(struct __vxge_hw_device *hldev)
{
	u16 cmd = 0;

	/* Set the PErr Repconse bit and SERR in PCI command register. */
	pci_read_config_word(hldev->pdev, PCI_COMMAND, &cmd);
	cmd |= 0x140;
	pci_write_config_word(hldev->pdev, PCI_COMMAND, cmd);

	pci_save_state(hldev->pdev);
}