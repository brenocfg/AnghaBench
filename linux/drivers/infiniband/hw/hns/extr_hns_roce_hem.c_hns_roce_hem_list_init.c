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
struct hns_roce_hem_list {int bt_pg_shift; int /*<<< orphan*/ ** mid_bt; int /*<<< orphan*/  btm_bt; int /*<<< orphan*/  root_bt; } ;

/* Variables and functions */
 int HNS_ROCE_MAX_BT_LEVEL ; 
 int HNS_ROCE_MAX_BT_REGION ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void hns_roce_hem_list_init(struct hns_roce_hem_list *hem_list,
			    int bt_page_order)
{
	int i, j;

	INIT_LIST_HEAD(&hem_list->root_bt);
	INIT_LIST_HEAD(&hem_list->btm_bt);
	for (i = 0; i < HNS_ROCE_MAX_BT_REGION; i++)
		for (j = 0; j < HNS_ROCE_MAX_BT_LEVEL; j++)
			INIT_LIST_HEAD(&hem_list->mid_bt[i][j]);

	hem_list->bt_pg_shift = bt_page_order;
}