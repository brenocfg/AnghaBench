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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct nicpf {int num_vf_en; int /*<<< orphan*/  flags; scalar_t__ num_sqs_en; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NIC_SRIOV_ENABLED ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 scalar_t__ PCI_SRIOV_TOTAL_VF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ nic_num_sqs_en (struct nicpf*,int) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int nic_sriov_init(struct pci_dev *pdev, struct nicpf *nic)
{
	int pos = 0;
	int vf_en;
	int err;
	u16 total_vf_cnt;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	if (!pos) {
		dev_err(&pdev->dev, "SRIOV capability is not found in PCIe config space\n");
		return -ENODEV;
	}

	pci_read_config_word(pdev, (pos + PCI_SRIOV_TOTAL_VF), &total_vf_cnt);
	if (total_vf_cnt < nic->num_vf_en)
		nic->num_vf_en = total_vf_cnt;

	if (!total_vf_cnt)
		return 0;

	vf_en = nic->num_vf_en;
	nic->num_sqs_en = nic_num_sqs_en(nic, nic->num_vf_en);
	vf_en += nic->num_sqs_en;

	err = pci_enable_sriov(pdev, vf_en);
	if (err) {
		dev_err(&pdev->dev, "SRIOV enable failed, num VF is %d\n",
			vf_en);
		nic->num_vf_en = 0;
		return err;
	}

	dev_info(&pdev->dev, "SRIOV enabled, number of VF available %d\n",
		 vf_en);

	nic->flags |= NIC_SRIOV_ENABLED;
	return 0;
}