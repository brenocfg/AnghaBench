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
typedef  int u16 ;

/* Variables and functions */
 unsigned char BIT (int) ; 
 scalar_t__ RF_1T1R ; 

u16 rtw_mcs_rate(u8 rf_type, u8 bw_40MHz, u8 short_GI, unsigned char *MCS_rate)
{
	u16 max_rate = 0;

	if (rf_type == RF_1T1R) {
		if (MCS_rate[0] & BIT(7))
			max_rate = (bw_40MHz) ? ((short_GI)?1500:1350):((short_GI)?722:650);
		else if (MCS_rate[0] & BIT(6))
			max_rate = (bw_40MHz) ? ((short_GI)?1350:1215):((short_GI)?650:585);
		else if (MCS_rate[0] & BIT(5))
			max_rate = (bw_40MHz) ? ((short_GI)?1200:1080):((short_GI)?578:520);
		else if (MCS_rate[0] & BIT(4))
			max_rate = (bw_40MHz) ? ((short_GI)?900:810):((short_GI)?433:390);
		else if (MCS_rate[0] & BIT(3))
			max_rate = (bw_40MHz) ? ((short_GI)?600:540):((short_GI)?289:260);
		else if (MCS_rate[0] & BIT(2))
			max_rate = (bw_40MHz) ? ((short_GI)?450:405):((short_GI)?217:195);
		else if (MCS_rate[0] & BIT(1))
			max_rate = (bw_40MHz) ? ((short_GI)?300:270):((short_GI)?144:130);
		else if (MCS_rate[0] & BIT(0))
			max_rate = (bw_40MHz) ? ((short_GI)?150:135):((short_GI)?72:65);
	} else {
		if (MCS_rate[1]) {
			if (MCS_rate[1] & BIT(7))
				max_rate = (bw_40MHz) ? ((short_GI)?3000:2700):((short_GI)?1444:1300);
			else if (MCS_rate[1] & BIT(6))
				max_rate = (bw_40MHz) ? ((short_GI)?2700:2430):((short_GI)?1300:1170);
			else if (MCS_rate[1] & BIT(5))
				max_rate = (bw_40MHz) ? ((short_GI)?2400:2160):((short_GI)?1156:1040);
			else if (MCS_rate[1] & BIT(4))
				max_rate = (bw_40MHz) ? ((short_GI)?1800:1620):((short_GI)?867:780);
			else if (MCS_rate[1] & BIT(3))
				max_rate = (bw_40MHz) ? ((short_GI)?1200:1080):((short_GI)?578:520);
			else if (MCS_rate[1] & BIT(2))
				max_rate = (bw_40MHz) ? ((short_GI)?900:810):((short_GI)?433:390);
			else if (MCS_rate[1] & BIT(1))
				max_rate = (bw_40MHz) ? ((short_GI)?600:540):((short_GI)?289:260);
			else if (MCS_rate[1] & BIT(0))
				max_rate = (bw_40MHz) ? ((short_GI)?300:270):((short_GI)?144:130);
		} else {
			if (MCS_rate[0] & BIT(7))
				max_rate = (bw_40MHz) ? ((short_GI)?1500:1350):((short_GI)?722:650);
			else if (MCS_rate[0] & BIT(6))
				max_rate = (bw_40MHz) ? ((short_GI)?1350:1215):((short_GI)?650:585);
			else if (MCS_rate[0] & BIT(5))
				max_rate = (bw_40MHz) ? ((short_GI)?1200:1080):((short_GI)?578:520);
			else if (MCS_rate[0] & BIT(4))
				max_rate = (bw_40MHz) ? ((short_GI)?900:810):((short_GI)?433:390);
			else if (MCS_rate[0] & BIT(3))
				max_rate = (bw_40MHz) ? ((short_GI)?600:540):((short_GI)?289:260);
			else if (MCS_rate[0] & BIT(2))
				max_rate = (bw_40MHz) ? ((short_GI)?450:405):((short_GI)?217:195);
			else if (MCS_rate[0] & BIT(1))
				max_rate = (bw_40MHz) ? ((short_GI)?300:270):((short_GI)?144:130);
			else if (MCS_rate[0] & BIT(0))
				max_rate = (bw_40MHz) ? ((short_GI)?150:135):((short_GI)?72:65);
		}
	}
	return max_rate;
}