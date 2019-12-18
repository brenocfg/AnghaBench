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
struct rtw_phy_stat_iter_data {int /*<<< orphan*/  min_rssi; struct rtw_dev* rtwdev; } ;
struct rtw_dm_info {int /*<<< orphan*/  min_rssi; int /*<<< orphan*/  pre_min_rssi; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  U8_MAX ; 
 int /*<<< orphan*/  rtw_iterate_stas_atomic (struct rtw_dev*,int /*<<< orphan*/ ,struct rtw_phy_stat_iter_data*) ; 
 int /*<<< orphan*/  rtw_phy_stat_rssi_iter ; 

__attribute__((used)) static void rtw_phy_stat_rssi(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	struct rtw_phy_stat_iter_data data = {};

	data.rtwdev = rtwdev;
	data.min_rssi = U8_MAX;
	rtw_iterate_stas_atomic(rtwdev, rtw_phy_stat_rssi_iter, &data);

	dm_info->pre_min_rssi = dm_info->min_rssi;
	dm_info->min_rssi = data.min_rssi;
}