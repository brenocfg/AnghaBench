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
typedef  int u32 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int rel_pf_id; struct qed_dev* cdev; } ;
struct qed_dev {int vendor_id; int device_id; int chip_num; int chip_rev; int num_hwfns; int chip_bond_id; int chip_metal; int /*<<< orphan*/  hwfns; int /*<<< orphan*/  type; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_BOND_ID ; 
 int /*<<< orphan*/  CHIP_METAL ; 
 int /*<<< orphan*/  CHIP_REV ; 
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,...) ; 
 int EBUSY ; 
 int /*<<< orphan*/  MASK_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MISCS_REG_CHIP_METAL ; 
 int /*<<< orphan*/  MISCS_REG_CHIP_NUM ; 
 int /*<<< orphan*/  MISCS_REG_CHIP_REV ; 
 int /*<<< orphan*/  MISCS_REG_CHIP_TEST_REG ; 
 int /*<<< orphan*/  MISCS_REG_CMT_ENABLED_FOR_PAIR ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int QED_DEV_ID_MASK ; 
#define  QED_DEV_ID_MASK_AH 129 
#define  QED_DEV_ID_MASK_BB 128 
 int /*<<< orphan*/  QED_DEV_TYPE_AH ; 
 int /*<<< orphan*/  QED_DEV_TYPE_BB ; 
 scalar_t__ QED_IS_BB (struct qed_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_get_dev_info(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	u16 device_id_mask;
	u32 tmp;

	/* Read Vendor Id / Device Id */
	pci_read_config_word(cdev->pdev, PCI_VENDOR_ID, &cdev->vendor_id);
	pci_read_config_word(cdev->pdev, PCI_DEVICE_ID, &cdev->device_id);

	/* Determine type */
	device_id_mask = cdev->device_id & QED_DEV_ID_MASK;
	switch (device_id_mask) {
	case QED_DEV_ID_MASK_BB:
		cdev->type = QED_DEV_TYPE_BB;
		break;
	case QED_DEV_ID_MASK_AH:
		cdev->type = QED_DEV_TYPE_AH;
		break;
	default:
		DP_NOTICE(p_hwfn, "Unknown device id 0x%x\n", cdev->device_id);
		return -EBUSY;
	}

	cdev->chip_num = (u16)qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_NUM);
	cdev->chip_rev = (u16)qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_REV);

	MASK_FIELD(CHIP_REV, cdev->chip_rev);

	/* Learn number of HW-functions */
	tmp = qed_rd(p_hwfn, p_ptt, MISCS_REG_CMT_ENABLED_FOR_PAIR);

	if (tmp & (1 << p_hwfn->rel_pf_id)) {
		DP_NOTICE(cdev->hwfns, "device in CMT mode\n");
		cdev->num_hwfns = 2;
	} else {
		cdev->num_hwfns = 1;
	}

	cdev->chip_bond_id = qed_rd(p_hwfn, p_ptt,
				    MISCS_REG_CHIP_TEST_REG) >> 4;
	MASK_FIELD(CHIP_BOND_ID, cdev->chip_bond_id);
	cdev->chip_metal = (u16)qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_METAL);
	MASK_FIELD(CHIP_METAL, cdev->chip_metal);

	DP_INFO(cdev->hwfns,
		"Chip details - %s %c%d, Num: %04x Rev: %04x Bond id: %04x Metal: %04x\n",
		QED_IS_BB(cdev) ? "BB" : "AH",
		'A' + cdev->chip_rev,
		(int)cdev->chip_metal,
		cdev->chip_num, cdev->chip_rev,
		cdev->chip_bond_id, cdev->chip_metal);

	return 0;
}