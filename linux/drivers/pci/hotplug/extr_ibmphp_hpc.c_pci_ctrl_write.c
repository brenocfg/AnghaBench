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
struct controller {scalar_t__ ctrl_dev; } ;

/* Variables and functions */
 scalar_t__ ENODEV ; 
 scalar_t__ HPC_PCI_OFFSET ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u8 pci_ctrl_write(struct controller *ctrl, u8 offset, u8 data)
{
	u8 rc = -ENODEV;
	debug("inside pci_ctrl_write\n");
	if (ctrl->ctrl_dev) {
		pci_write_config_byte(ctrl->ctrl_dev, HPC_PCI_OFFSET + offset, data);
		rc = 0;
	}
	return rc;
}