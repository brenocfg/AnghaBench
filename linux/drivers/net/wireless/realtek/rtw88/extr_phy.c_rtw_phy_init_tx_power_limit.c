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
typedef  size_t u8 ;
struct rtw_hal {void***** tx_pwr_limit_5g; void***** tx_pwr_limit_2g; } ;
struct rtw_dev {TYPE_1__* chip; struct rtw_hal hal; } ;
typedef  void* s8 ;
struct TYPE_2__ {int /*<<< orphan*/  max_power_index; } ;

/* Variables and functions */
 size_t RTW_MAX_CHANNEL_NUM_2G ; 
 size_t RTW_MAX_CHANNEL_NUM_5G ; 

__attribute__((used)) static void rtw_phy_init_tx_power_limit(struct rtw_dev *rtwdev,
					u8 regd, u8 bw, u8 rs)
{
	struct rtw_hal *hal = &rtwdev->hal;
	s8 max_power_index = (s8)rtwdev->chip->max_power_index;
	u8 ch;

	/* 2.4G channels */
	for (ch = 0; ch < RTW_MAX_CHANNEL_NUM_2G; ch++)
		hal->tx_pwr_limit_2g[regd][bw][rs][ch] = max_power_index;

	/* 5G channels */
	for (ch = 0; ch < RTW_MAX_CHANNEL_NUM_5G; ch++)
		hal->tx_pwr_limit_5g[regd][bw][rs][ch] = max_power_index;
}