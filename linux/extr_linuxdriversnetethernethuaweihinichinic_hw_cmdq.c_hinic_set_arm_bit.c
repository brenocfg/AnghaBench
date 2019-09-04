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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_cmdqs {struct hinic_hwif* hwif; struct hinic_cmdq* cmdq; } ;
struct hinic_cmdq_arm_bit {int q_type; int /*<<< orphan*/  q_id; } ;
struct hinic_cmdq {int dummy; } ;
typedef  enum hinic_set_arm_qtype { ____Placeholder_hinic_set_arm_qtype } hinic_set_arm_qtype ;
typedef  int /*<<< orphan*/  arm_bit ;

/* Variables and functions */
 size_t HINIC_CMDQ_SYNC ; 
 int cmdq_set_arm_bit (struct hinic_cmdq*,struct hinic_cmdq_arm_bit*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int hinic_set_arm_bit(struct hinic_cmdqs *cmdqs,
		      enum hinic_set_arm_qtype q_type, u32 q_id)
{
	struct hinic_cmdq *cmdq = &cmdqs->cmdq[HINIC_CMDQ_SYNC];
	struct hinic_hwif *hwif = cmdqs->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_cmdq_arm_bit arm_bit;
	int err;

	arm_bit.q_type = q_type;
	arm_bit.q_id   = q_id;

	err = cmdq_set_arm_bit(cmdq, &arm_bit, sizeof(arm_bit));
	if (err) {
		dev_err(&pdev->dev, "Failed to set arm for qid %d\n", q_id);
		return err;
	}

	return 0;
}