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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rq_num {scalar_t__ status; int /*<<< orphan*/  rq_depth; int /*<<< orphan*/  num_rqs; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  rq_num ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_RQ_IQ_MAP ; 
 int /*<<< orphan*/  HINIC_SQ_DEPTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rq_num*,int,struct hinic_rq_num*,int*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 

int hinic_set_max_qnum(struct hinic_dev *nic_dev, u8 num_rqs)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_rq_num rq_num = { 0 };
	u16 out_size = sizeof(rq_num);
	int err;

	rq_num.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	rq_num.num_rqs = num_rqs;
	rq_num.rq_depth = ilog2(HINIC_SQ_DEPTH);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RQ_IQ_MAP,
				 &rq_num, sizeof(rq_num),
				 &rq_num, &out_size);
	if (err || !out_size || rq_num.status) {
		dev_err(&pdev->dev,
			"Failed to rxq number, ret = %d\n",
			rq_num.status);
		return -EINVAL;
	}

	return 0;
}