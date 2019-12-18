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
struct rtw_hal {size_t** tx_pwr_tbl; } ;
struct rtw_dev {struct rtw_hal hal; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 size_t DESC_RATE11M ; 
 size_t DESC_RATEMCS7 ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 size_t RTW_RATE_SECTION_MAX ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtw8822c_set_tx_power_diff (struct rtw_dev*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  rtw8822c_set_write_tx_power_ref (struct rtw_dev*,size_t*,size_t*) ; 
 size_t** rtw_rate_section ; 
 size_t* rtw_rate_size ; 

__attribute__((used)) static void rtw8822c_set_tx_power_index(struct rtw_dev *rtwdev)
{
	struct rtw_hal *hal = &rtwdev->hal;
	u8 rs, rate, j;
	u8 pwr_ref_cck[2] = {hal->tx_pwr_tbl[RF_PATH_A][DESC_RATE11M],
			     hal->tx_pwr_tbl[RF_PATH_B][DESC_RATE11M]};
	u8 pwr_ref_ofdm[2] = {hal->tx_pwr_tbl[RF_PATH_A][DESC_RATEMCS7],
			      hal->tx_pwr_tbl[RF_PATH_B][DESC_RATEMCS7]};
	s8 diff_a, diff_b;
	u8 pwr_a, pwr_b;
	s8 diff_idx[4];

	rtw8822c_set_write_tx_power_ref(rtwdev, pwr_ref_cck, pwr_ref_ofdm);
	for (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++) {
		for (j = 0; j < rtw_rate_size[rs]; j++) {
			rate = rtw_rate_section[rs][j];
			pwr_a = hal->tx_pwr_tbl[RF_PATH_A][rate];
			pwr_b = hal->tx_pwr_tbl[RF_PATH_B][rate];
			if (rs == 0) {
				diff_a = (s8)pwr_a - (s8)pwr_ref_cck[0];
				diff_b = (s8)pwr_b - (s8)pwr_ref_cck[1];
			} else {
				diff_a = (s8)pwr_a - (s8)pwr_ref_ofdm[0];
				diff_b = (s8)pwr_b - (s8)pwr_ref_ofdm[1];
			}
			diff_idx[rate % 4] = min(diff_a, diff_b);
			if (rate % 4 == 3)
				rtw8822c_set_tx_power_diff(rtwdev, rate - 3,
							   diff_idx);
		}
	}
}