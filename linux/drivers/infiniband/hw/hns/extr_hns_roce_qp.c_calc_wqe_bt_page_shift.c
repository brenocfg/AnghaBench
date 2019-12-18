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
struct TYPE_2__ {int mtt_ba_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
struct hns_roce_buf_region {int dummy; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int PAGE_SHIFT ; 
 int hns_roce_hem_list_calc_root_ba (struct hns_roce_buf_region*,int,int) ; 

__attribute__((used)) static int calc_wqe_bt_page_shift(struct hns_roce_dev *hr_dev,
				  struct hns_roce_buf_region *regions,
				  int region_cnt)
{
	int bt_pg_shift;
	int ba_num;
	int ret;

	bt_pg_shift = PAGE_SHIFT + hr_dev->caps.mtt_ba_pg_sz;

	/* all root ba entries must in one bt page */
	do {
		ba_num = (1 << bt_pg_shift) / BA_BYTE_LEN;
		ret = hns_roce_hem_list_calc_root_ba(regions, region_cnt,
						     ba_num);
		if (ret <= ba_num)
			break;

		bt_pg_shift++;
	} while (ret > ba_num);

	return bt_pg_shift - PAGE_SHIFT;
}