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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtw_dm_info {scalar_t__ min_rssi; scalar_t__ pre_min_rssi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_CVRG_FA_TH_EXTRA_HIGH ; 
 int /*<<< orphan*/  DIG_CVRG_FA_TH_HIGH ; 
 int /*<<< orphan*/  DIG_CVRG_FA_TH_LOW ; 
 int /*<<< orphan*/  DIG_PERF_FA_TH_EXTRA_HIGH ; 
 int /*<<< orphan*/  DIG_PERF_FA_TH_HIGH ; 
 int /*<<< orphan*/  DIG_PERF_FA_TH_LOW ; 

__attribute__((used)) static void rtw_phy_dig_get_threshold(struct rtw_dm_info *dm_info,
				      u16 *fa_th, u8 *step, bool linked)
{
	u8 min_rssi, pre_min_rssi;

	min_rssi = dm_info->min_rssi;
	pre_min_rssi = dm_info->pre_min_rssi;
	step[0] = 4;
	step[1] = 3;
	step[2] = 2;

	if (linked) {
		fa_th[0] = DIG_PERF_FA_TH_EXTRA_HIGH;
		fa_th[1] = DIG_PERF_FA_TH_HIGH;
		fa_th[2] = DIG_PERF_FA_TH_LOW;
		if (pre_min_rssi > min_rssi) {
			step[0] = 6;
			step[1] = 4;
			step[2] = 2;
		}
	} else {
		fa_th[0] = DIG_CVRG_FA_TH_EXTRA_HIGH;
		fa_th[1] = DIG_CVRG_FA_TH_HIGH;
		fa_th[2] = DIG_CVRG_FA_TH_LOW;
	}
}