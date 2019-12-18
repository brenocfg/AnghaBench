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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_BRK_TABLE_VAL ; 
 int /*<<< orphan*/  REG_BT_COEX_BRK_TABLE ; 
 int /*<<< orphan*/  REG_BT_COEX_TABLE0 ; 
 int /*<<< orphan*/  REG_BT_COEX_TABLE1 ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_set_table(struct rtw_dev *rtwdev, u32 table0, u32 table1)
{
#define DEF_BRK_TABLE_VAL	0xf0ffffff
	rtw_write32(rtwdev, REG_BT_COEX_TABLE0, table0);
	rtw_write32(rtwdev, REG_BT_COEX_TABLE1, table1);
	rtw_write32(rtwdev, REG_BT_COEX_BRK_TABLE, DEF_BRK_TABLE_VAL);
}