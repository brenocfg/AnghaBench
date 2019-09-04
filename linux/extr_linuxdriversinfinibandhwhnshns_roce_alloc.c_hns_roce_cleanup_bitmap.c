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
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_cleanup_cq_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_mr_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_pd_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_qp_table (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_uar_table (struct hns_roce_dev*) ; 

void hns_roce_cleanup_bitmap(struct hns_roce_dev *hr_dev)
{
	hns_roce_cleanup_qp_table(hr_dev);
	hns_roce_cleanup_cq_table(hr_dev);
	hns_roce_cleanup_mr_table(hr_dev);
	hns_roce_cleanup_pd_table(hr_dev);
	hns_roce_cleanup_uar_table(hr_dev);
}