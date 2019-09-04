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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ check_whether_bt_num_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_whether_bt_num_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_whether_bt_num_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_get_bt_num(u32 table_type, u32 hop_num)
{
	if (check_whether_bt_num_3(table_type, hop_num))
		return 3;
	else if (check_whether_bt_num_2(table_type, hop_num))
		return 2;
	else if (check_whether_bt_num_1(table_type, hop_num))
		return 1;
	else
		return 0;
}