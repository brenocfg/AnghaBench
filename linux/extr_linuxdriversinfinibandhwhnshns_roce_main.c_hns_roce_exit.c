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
struct hns_roce_dev {TYPE_1__* hw; scalar_t__ cmd_mod; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct hns_roce_dev*,int) ;int /*<<< orphan*/  (* cmq_exit ) (struct hns_roce_dev*) ;int /*<<< orphan*/  (* cleanup_eq ) (struct hns_roce_dev*) ;int /*<<< orphan*/  (* hw_exit ) (struct hns_roce_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_cleanup_bitmap (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cleanup_hem (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cmd_cleanup (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_cmd_use_polling (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_unregister_device (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  stub1 (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  stub2 (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  stub3 (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  stub4 (struct hns_roce_dev*,int) ; 

void hns_roce_exit(struct hns_roce_dev *hr_dev)
{
	hns_roce_unregister_device(hr_dev);

	if (hr_dev->hw->hw_exit)
		hr_dev->hw->hw_exit(hr_dev);
	hns_roce_cleanup_bitmap(hr_dev);
	hns_roce_cleanup_hem(hr_dev);

	if (hr_dev->cmd_mod)
		hns_roce_cmd_use_polling(hr_dev);

	hr_dev->hw->cleanup_eq(hr_dev);
	hns_roce_cmd_cleanup(hr_dev);
	if (hr_dev->hw->cmq_exit)
		hr_dev->hw->cmq_exit(hr_dev);
	if (hr_dev->hw->reset)
		hr_dev->hw->reset(hr_dev, false);
}