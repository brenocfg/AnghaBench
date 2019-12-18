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
struct rtw_txpwr_idx {int /*<<< orphan*/  pwr_idx_5g; int /*<<< orphan*/  pwr_idx_2g; } ;
struct rtw_power_params {size_t pwr_base; int /*<<< orphan*/  pwr_limit; int /*<<< orphan*/  pwr_offset; } ;
struct rtw_hal {int /*<<< orphan*/ ** tx_pwr_by_rate_offset_5g; int /*<<< orphan*/ ** tx_pwr_by_rate_offset_2g; } ;
struct TYPE_2__ {struct rtw_txpwr_idx* txpwr_idx_table; } ;
struct rtw_dev {TYPE_1__ efuse; struct rtw_hal hal; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t PHY_BAND_2G ; 
 size_t PHY_BAND_5G ; 
 size_t rtw_get_channel_group (size_t) ; 
 size_t rtw_phy_get_2g_tx_power_index (struct rtw_dev*,int /*<<< orphan*/ *,size_t,size_t,size_t) ; 
 size_t rtw_phy_get_5g_tx_power_index (struct rtw_dev*,int /*<<< orphan*/ *,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  rtw_phy_get_tx_power_limit (struct rtw_dev*,size_t,size_t,size_t,size_t,size_t,size_t) ; 

void rtw_get_tx_power_params(struct rtw_dev *rtwdev, u8 path, u8 rate, u8 bw,
			     u8 ch, u8 regd, struct rtw_power_params *pwr_param)
{
	struct rtw_hal *hal = &rtwdev->hal;
	struct rtw_txpwr_idx *pwr_idx;
	u8 group, band;
	u8 *base = &pwr_param->pwr_base;
	s8 *offset = &pwr_param->pwr_offset;
	s8 *limit = &pwr_param->pwr_limit;

	pwr_idx = &rtwdev->efuse.txpwr_idx_table[path];
	group = rtw_get_channel_group(ch);

	/* base power index for 2.4G/5G */
	if (ch <= 14) {
		band = PHY_BAND_2G;
		*base = rtw_phy_get_2g_tx_power_index(rtwdev,
						      &pwr_idx->pwr_idx_2g,
						      bw, rate, group);
		*offset = hal->tx_pwr_by_rate_offset_2g[path][rate];
	} else {
		band = PHY_BAND_5G;
		*base = rtw_phy_get_5g_tx_power_index(rtwdev,
						      &pwr_idx->pwr_idx_5g,
						      bw, rate, group);
		*offset = hal->tx_pwr_by_rate_offset_5g[path][rate];
	}

	*limit = rtw_phy_get_tx_power_limit(rtwdev, band, bw, path,
					    rate, ch, regd);
}