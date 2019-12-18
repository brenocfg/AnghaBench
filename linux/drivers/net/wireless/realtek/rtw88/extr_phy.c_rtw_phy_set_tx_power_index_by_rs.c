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
struct rtw_hal {size_t current_band_width; size_t** tx_pwr_tbl; } ;
struct TYPE_2__ {size_t txpwr_regd; } ;
struct rtw_dev {TYPE_1__ regd; struct rtw_hal hal; } ;

/* Variables and functions */
 size_t RTW_RATE_SECTION_MAX ; 
 size_t rtw_phy_get_tx_power_index (struct rtw_dev*,size_t,size_t,size_t,size_t,size_t) ; 
 size_t** rtw_rate_section ; 
 size_t* rtw_rate_size ; 

__attribute__((used)) static void rtw_phy_set_tx_power_index_by_rs(struct rtw_dev *rtwdev,
					     u8 ch, u8 path, u8 rs)
{
	struct rtw_hal *hal = &rtwdev->hal;
	u8 regd = rtwdev->regd.txpwr_regd;
	u8 *rates;
	u8 size;
	u8 rate;
	u8 pwr_idx;
	u8 bw;
	int i;

	if (rs >= RTW_RATE_SECTION_MAX)
		return;

	rates = rtw_rate_section[rs];
	size = rtw_rate_size[rs];
	bw = hal->current_band_width;
	for (i = 0; i < size; i++) {
		rate = rates[i];
		pwr_idx = rtw_phy_get_tx_power_index(rtwdev, path, rate,
						     bw, ch, regd);
		hal->tx_pwr_tbl[path][rate] = pwr_idx;
	}
}