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
struct hns_roce_hem_list {scalar_t__ root_ba; int /*<<< orphan*/  btm_bt; int /*<<< orphan*/  root_bt; int /*<<< orphan*/ ** mid_bt; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int HNS_ROCE_MAX_BT_LEVEL ; 
 int HNS_ROCE_MAX_BT_REGION ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hem_list_free_all (struct hns_roce_dev*,int /*<<< orphan*/ *,int) ; 

void hns_roce_hem_list_release(struct hns_roce_dev *hr_dev,
			       struct hns_roce_hem_list *hem_list)
{
	int i, j;

	for (i = 0; i < HNS_ROCE_MAX_BT_REGION; i++)
		for (j = 0; j < HNS_ROCE_MAX_BT_LEVEL; j++)
			hem_list_free_all(hr_dev, &hem_list->mid_bt[i][j],
					  j != 0);

	hem_list_free_all(hr_dev, &hem_list->root_bt, true);
	INIT_LIST_HEAD(&hem_list->btm_bt);
	hem_list->root_ba = 0;
}