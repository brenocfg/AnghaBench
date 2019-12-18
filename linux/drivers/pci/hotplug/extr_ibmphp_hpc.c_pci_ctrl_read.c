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
typedef  int u8 ;
struct controller {scalar_t__ ctrl_dev; } ;

/* Variables and functions */
 int HPC_PCI_OFFSET ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  pci_read_config_byte (scalar_t__,int,int*) ; 

__attribute__((used)) static u8 pci_ctrl_read(struct controller *ctrl, u8 offset)
{
	u8 data = 0x00;
	debug("inside pci_ctrl_read\n");
	if (ctrl->ctrl_dev)
		pci_read_config_byte(ctrl->ctrl_dev, HPC_PCI_OFFSET + offset, &data);
	return data;
}