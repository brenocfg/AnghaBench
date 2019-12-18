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
 int /*<<< orphan*/  HNS_ROCE_PORT_DOWN ; 
 int /*<<< orphan*/  hns_roce_bt_free (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_db_free (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_free_mr_free (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_port_enable (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_raq_free (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_tptr_free (struct hns_roce_dev*) ; 

__attribute__((used)) static void hns_roce_v1_exit(struct hns_roce_dev *hr_dev)
{
	hns_roce_port_enable(hr_dev, HNS_ROCE_PORT_DOWN);
	hns_roce_free_mr_free(hr_dev);
	hns_roce_tptr_free(hr_dev);
	hns_roce_bt_free(hr_dev);
	hns_roce_raq_free(hr_dev);
	hns_roce_db_free(hr_dev);
}