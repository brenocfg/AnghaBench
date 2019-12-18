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
struct hns_roce_mtr {int /*<<< orphan*/  hem_list; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_hem_list_release (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 

void hns_roce_mtr_cleanup(struct hns_roce_dev *hr_dev,
			  struct hns_roce_mtr *mtr)
{
	hns_roce_hem_list_release(hr_dev, &mtr->hem_list);
}