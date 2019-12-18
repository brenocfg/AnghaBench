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
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HEM_TYPE_CQC 134 
#define  HEM_TYPE_CQC_TIMER 133 
#define  HEM_TYPE_MTPT 132 
#define  HEM_TYPE_QPC 131 
#define  HEM_TYPE_QPC_TIMER 130 
#define  HEM_TYPE_SCCC 129 
#define  HEM_TYPE_SRQC 128 
 int HNS_ROCE_CMD_WRITE_CQC_BT0 ; 
 int HNS_ROCE_CMD_WRITE_CQC_TIMER_BT0 ; 
 int HNS_ROCE_CMD_WRITE_MPT_BT0 ; 
 int HNS_ROCE_CMD_WRITE_QPC_BT0 ; 
 int HNS_ROCE_CMD_WRITE_QPC_TIMER_BT0 ; 
 int HNS_ROCE_CMD_WRITE_SCCC_BT0 ; 
 int HNS_ROCE_CMD_WRITE_SRQC_BT0 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int get_op_for_set_hem(struct hns_roce_dev *hr_dev, u32 type,
			      int step_idx)
{
	int op;

	if (type == HEM_TYPE_SCCC && step_idx)
		return -EINVAL;

	switch (type) {
	case HEM_TYPE_QPC:
		op = HNS_ROCE_CMD_WRITE_QPC_BT0;
		break;
	case HEM_TYPE_MTPT:
		op = HNS_ROCE_CMD_WRITE_MPT_BT0;
		break;
	case HEM_TYPE_CQC:
		op = HNS_ROCE_CMD_WRITE_CQC_BT0;
		break;
	case HEM_TYPE_SRQC:
		op = HNS_ROCE_CMD_WRITE_SRQC_BT0;
		break;
	case HEM_TYPE_SCCC:
		op = HNS_ROCE_CMD_WRITE_SCCC_BT0;
		break;
	case HEM_TYPE_QPC_TIMER:
		op = HNS_ROCE_CMD_WRITE_QPC_TIMER_BT0;
		break;
	case HEM_TYPE_CQC_TIMER:
		op = HNS_ROCE_CMD_WRITE_CQC_TIMER_BT0;
		break;
	default:
		dev_warn(hr_dev->dev,
			 "Table %d not to be written by mailbox!\n", type);
		return -EINVAL;
	}

	return op + step_idx;
}