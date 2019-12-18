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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw8822c_dpk_mac_bb_tbl ; 
 int /*<<< orphan*/  rtw8822c_dpk_tx_pause (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_load_table (struct rtw_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw8822c_dpk_mac_bb_setting(struct rtw_dev *rtwdev)
{
	rtw8822c_dpk_tx_pause(rtwdev);
	rtw_load_table(rtwdev, &rtw8822c_dpk_mac_bb_tbl);
}