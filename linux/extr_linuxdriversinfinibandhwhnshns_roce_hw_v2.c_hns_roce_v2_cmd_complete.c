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
struct hns_roce_dev {scalar_t__ reg_base; } ;

/* Variables and functions */
 int HNS_ROCE_HW_MB_STATUS_MASK ; 
 scalar_t__ ROCEE_VF_MB_STATUS_REG ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int hns_roce_v2_cmd_complete(struct hns_roce_dev *hr_dev)
{
	u32 status = readl(hr_dev->reg_base + ROCEE_VF_MB_STATUS_REG);

	return status & HNS_ROCE_HW_MB_STATUS_MASK;
}