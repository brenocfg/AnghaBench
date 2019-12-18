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
struct rtw_hal {scalar_t__** tx_pwr_by_rate_offset_5g; scalar_t__** tx_pwr_by_rate_offset_2g; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */
 size_t DESC_RATE_MAX ; 
 size_t RTW_CHANNEL_WIDTH_MAX ; 
 size_t RTW_RATE_SECTION_MAX ; 
 size_t RTW_REGD_MAX ; 
 size_t RTW_RF_PATH_MAX ; 
 int /*<<< orphan*/  rtw_phy_init_tx_power_limit (struct rtw_dev*,size_t,size_t,size_t) ; 

void rtw_phy_init_tx_power(struct rtw_dev *rtwdev)
{
	struct rtw_hal *hal = &rtwdev->hal;
	u8 regd, path, rate, rs, bw;

	/* init tx power by rate offset */
	for (path = 0; path < RTW_RF_PATH_MAX; path++) {
		for (rate = 0; rate < DESC_RATE_MAX; rate++) {
			hal->tx_pwr_by_rate_offset_2g[path][rate] = 0;
			hal->tx_pwr_by_rate_offset_5g[path][rate] = 0;
		}
	}

	/* init tx power limit */
	for (regd = 0; regd < RTW_REGD_MAX; regd++)
		for (bw = 0; bw < RTW_CHANNEL_WIDTH_MAX; bw++)
			for (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++)
				rtw_phy_init_tx_power_limit(rtwdev, regd, bw,
							    rs);
}