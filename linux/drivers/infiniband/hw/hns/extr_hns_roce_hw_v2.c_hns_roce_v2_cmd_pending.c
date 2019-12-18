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
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int HNS_ROCE_HW_RUN_BIT_SHIFT ; 
 int hns_roce_query_mbox_status (struct hns_roce_dev*) ; 

__attribute__((used)) static int hns_roce_v2_cmd_pending(struct hns_roce_dev *hr_dev)
{
	u32 status = hns_roce_query_mbox_status(hr_dev);

	return status >> HNS_ROCE_HW_RUN_BIT_SHIFT;
}