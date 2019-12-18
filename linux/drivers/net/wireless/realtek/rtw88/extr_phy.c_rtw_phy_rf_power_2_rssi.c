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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int sum ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int FRAC_BITS ; 
 int rtw_phy_db_2_linear (size_t) ; 
 size_t rtw_phy_linear_2_db (int) ; 
 size_t rtw_phy_power_2_db (int /*<<< orphan*/ ) ; 

u8 rtw_phy_rf_power_2_rssi(s8 *rf_power, u8 path_num)
{
	s8 power;
	u8 power_db;
	u64 linear;
	u64 sum = 0;
	u8 path;

	for (path = 0; path < path_num; path++) {
		power = rf_power[path];
		power_db = rtw_phy_power_2_db(power);
		linear = rtw_phy_db_2_linear(power_db);
		sum += linear;
	}

	sum = (sum + (1 << (FRAC_BITS - 1))) >> FRAC_BITS;
	switch (path_num) {
	case 2:
		sum >>= 1;
		break;
	case 3:
		sum = ((sum) + ((sum) << 1) + ((sum) << 3)) >> 5;
		break;
	case 4:
		sum >>= 2;
		break;
	default:
		break;
	}

	return rtw_phy_linear_2_db(sum);
}