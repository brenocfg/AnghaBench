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
struct rtw_hal {int* cch_by_bw; } ;

/* Variables and functions */
 size_t RTW_CHANNEL_WIDTH_20 ; 
 scalar_t__ RTW_CHANNEL_WIDTH_MAX ; 
 scalar_t__ RTW_RATE_SECTION_MAX ; 
 scalar_t__ RTW_REGD_MAX ; 
 int /*<<< orphan*/  __rtw_phy_tx_power_limit_config (struct rtw_hal*,scalar_t__,scalar_t__,scalar_t__) ; 

void rtw_phy_tx_power_limit_config(struct rtw_hal *hal)
{
	u8 regd, bw, rs;

	/* default at channel 1 */
	hal->cch_by_bw[RTW_CHANNEL_WIDTH_20] = 1;

	for (regd = 0; regd < RTW_REGD_MAX; regd++)
		for (bw = 0; bw < RTW_CHANNEL_WIDTH_MAX; bw++)
			for (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++)
				__rtw_phy_tx_power_limit_config(hal, regd, bw, rs);
}