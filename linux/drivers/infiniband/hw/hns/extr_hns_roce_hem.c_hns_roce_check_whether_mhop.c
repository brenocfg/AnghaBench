#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int qpc_hop_num; int mpt_hop_num; int cqc_hop_num; int srqc_hop_num; int sccc_hop_num; int qpc_timer_hop_num; int cqc_timer_hop_num; int cqe_hop_num; int mtt_hop_num; int srqwqe_hop_num; int idx_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;

/* Variables and functions */
#define  HEM_TYPE_CQC 138 
#define  HEM_TYPE_CQC_TIMER 137 
#define  HEM_TYPE_CQE 136 
#define  HEM_TYPE_IDX 135 
#define  HEM_TYPE_MTPT 134 
#define  HEM_TYPE_MTT 133 
#define  HEM_TYPE_QPC 132 
#define  HEM_TYPE_QPC_TIMER 131 
#define  HEM_TYPE_SCCC 130 
#define  HEM_TYPE_SRQC 129 
#define  HEM_TYPE_SRQWQE 128 

bool hns_roce_check_whether_mhop(struct hns_roce_dev *hr_dev, u32 type)
{
	int hop_num = 0;

	switch (type) {
	case HEM_TYPE_QPC:
		hop_num = hr_dev->caps.qpc_hop_num;
		break;
	case HEM_TYPE_MTPT:
		hop_num = hr_dev->caps.mpt_hop_num;
		break;
	case HEM_TYPE_CQC:
		hop_num = hr_dev->caps.cqc_hop_num;
		break;
	case HEM_TYPE_SRQC:
		hop_num = hr_dev->caps.srqc_hop_num;
		break;
	case HEM_TYPE_SCCC:
		hop_num = hr_dev->caps.sccc_hop_num;
		break;
	case HEM_TYPE_QPC_TIMER:
		hop_num = hr_dev->caps.qpc_timer_hop_num;
		break;
	case HEM_TYPE_CQC_TIMER:
		hop_num = hr_dev->caps.cqc_timer_hop_num;
		break;
	case HEM_TYPE_CQE:
		hop_num = hr_dev->caps.cqe_hop_num;
		break;
	case HEM_TYPE_MTT:
		hop_num = hr_dev->caps.mtt_hop_num;
		break;
	case HEM_TYPE_SRQWQE:
		hop_num = hr_dev->caps.srqwqe_hop_num;
		break;
	case HEM_TYPE_IDX:
		hop_num = hr_dev->caps.idx_hop_num;
		break;
	default:
		return false;
	}

	return hop_num ? true : false;
}