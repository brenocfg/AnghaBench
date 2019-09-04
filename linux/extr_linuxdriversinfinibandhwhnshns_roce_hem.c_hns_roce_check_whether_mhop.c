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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ mtt_hop_num; scalar_t__ cqe_hop_num; scalar_t__ srqc_hop_num; scalar_t__ cqc_hop_num; scalar_t__ mpt_hop_num; scalar_t__ qpc_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 scalar_t__ HEM_TYPE_CQC ; 
 scalar_t__ HEM_TYPE_CQE ; 
 scalar_t__ HEM_TYPE_MTPT ; 
 scalar_t__ HEM_TYPE_MTT ; 
 scalar_t__ HEM_TYPE_QPC ; 
 scalar_t__ HEM_TYPE_SRQC ; 

bool hns_roce_check_whether_mhop(struct hns_roce_dev *hr_dev, u32 type)
{
	if ((hr_dev->caps.qpc_hop_num && type == HEM_TYPE_QPC) ||
	    (hr_dev->caps.mpt_hop_num && type == HEM_TYPE_MTPT) ||
	    (hr_dev->caps.cqc_hop_num && type == HEM_TYPE_CQC) ||
	    (hr_dev->caps.srqc_hop_num && type == HEM_TYPE_SRQC) ||
	    (hr_dev->caps.cqe_hop_num && type == HEM_TYPE_CQE) ||
	    (hr_dev->caps.mtt_hop_num && type == HEM_TYPE_MTT))
		return true;

	return false;
}