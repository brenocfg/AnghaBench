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
typedef  unsigned int u32 ;
struct pci_dev {int dummy; } ;
struct icm {int vnd_cap; struct pci_dev* upstream_port; } ;
typedef  enum tb_cfg_space { ____Placeholder_tb_cfg_space } tb_cfg_space ;

/* Variables and functions */
 scalar_t__ PCIE2CIO_CMD ; 
 int PCIE2CIO_CMD_CS_MASK ; 
 int PCIE2CIO_CMD_CS_SHIFT ; 
 unsigned int PCIE2CIO_CMD_PORT_MASK ; 
 unsigned int PCIE2CIO_CMD_PORT_SHIFT ; 
 unsigned int PCIE2CIO_CMD_START ; 
 unsigned int PCIE2CIO_CMD_WRITE ; 
 scalar_t__ PCIE2CIO_WRDATA ; 
 int pci2cio_wait_completion (struct icm*,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,unsigned int) ; 

__attribute__((used)) static int pcie2cio_write(struct icm *icm, enum tb_cfg_space cs,
			  unsigned int port, unsigned int index, u32 data)
{
	struct pci_dev *pdev = icm->upstream_port;
	int vnd_cap = icm->vnd_cap;
	u32 cmd;

	pci_write_config_dword(pdev, vnd_cap + PCIE2CIO_WRDATA, data);

	cmd = index;
	cmd |= (port << PCIE2CIO_CMD_PORT_SHIFT) & PCIE2CIO_CMD_PORT_MASK;
	cmd |= (cs << PCIE2CIO_CMD_CS_SHIFT) & PCIE2CIO_CMD_CS_MASK;
	cmd |= PCIE2CIO_CMD_WRITE | PCIE2CIO_CMD_START;
	pci_write_config_dword(pdev, vnd_cap + PCIE2CIO_CMD, cmd);

	return pci2cio_wait_completion(icm, 5000);
}