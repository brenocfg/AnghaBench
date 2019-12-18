#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct qla_hw_data {TYPE_3__* pdev; int /*<<< orphan*/  chip_revision; } ;
struct TYPE_9__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_10__ {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int QLA_SUCCESS ; 
 scalar_t__ pci_is_pcie (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_set_readrq (TYPE_3__*,int) ; 

int
qlafx00_pci_config(scsi_qla_host_t *vha)
{
	uint16_t w;
	struct qla_hw_data *ha = vha->hw;

	pci_set_master(ha->pdev);
	pci_try_set_mwi(ha->pdev);

	pci_read_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= (PCI_COMMAND_PARITY | PCI_COMMAND_SERR);
	w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_write_config_word(ha->pdev, PCI_COMMAND, w);

	/* PCIe -- adjust Maximum Read Request Size (2048). */
	if (pci_is_pcie(ha->pdev))
		pcie_set_readrq(ha->pdev, 2048);

	ha->chip_revision = ha->pdev->revision;

	return QLA_SUCCESS;
}