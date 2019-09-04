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
struct bnx2x_sriov {int pos; int /*<<< orphan*/  link; int /*<<< orphan*/  cap; int /*<<< orphan*/  pgsz; int /*<<< orphan*/  stride; int /*<<< orphan*/  offset; int /*<<< orphan*/  initial; int /*<<< orphan*/  total; int /*<<< orphan*/  ctrl; } ;
struct bnx2x {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 scalar_t__ PCI_SRIOV_CAP ; 
 scalar_t__ PCI_SRIOV_CTRL ; 
 scalar_t__ PCI_SRIOV_FUNC_LINK ; 
 scalar_t__ PCI_SRIOV_INITIAL_VF ; 
 scalar_t__ PCI_SRIOV_SUP_PGSIZE ; 
 scalar_t__ PCI_SRIOV_TOTAL_VF ; 
 scalar_t__ PCI_SRIOV_VF_OFFSET ; 
 scalar_t__ PCI_SRIOV_VF_STRIDE ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_sriov_pci_cfg_info(struct bnx2x *bp, struct bnx2x_sriov *iov)
{
	int pos;
	struct pci_dev *dev = bp->pdev;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV);
	if (!pos) {
		BNX2X_ERR("failed to find SRIOV capability in device\n");
		return -ENODEV;
	}

	iov->pos = pos;
	DP(BNX2X_MSG_IOV, "sriov ext pos %d\n", pos);
	pci_read_config_word(dev, pos + PCI_SRIOV_CTRL, &iov->ctrl);
	pci_read_config_word(dev, pos + PCI_SRIOV_TOTAL_VF, &iov->total);
	pci_read_config_word(dev, pos + PCI_SRIOV_INITIAL_VF, &iov->initial);
	pci_read_config_word(dev, pos + PCI_SRIOV_VF_OFFSET, &iov->offset);
	pci_read_config_word(dev, pos + PCI_SRIOV_VF_STRIDE, &iov->stride);
	pci_read_config_dword(dev, pos + PCI_SRIOV_SUP_PGSIZE, &iov->pgsz);
	pci_read_config_dword(dev, pos + PCI_SRIOV_CAP, &iov->cap);
	pci_read_config_byte(dev, pos + PCI_SRIOV_FUNC_LINK, &iov->link);

	return 0;
}