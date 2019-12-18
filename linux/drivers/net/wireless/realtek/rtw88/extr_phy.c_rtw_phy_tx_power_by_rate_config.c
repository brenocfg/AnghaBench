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
struct rtw_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_RATE_SECTION_CCK ; 
 int /*<<< orphan*/  RTW_RATE_SECTION_HT_1S ; 
 int /*<<< orphan*/  RTW_RATE_SECTION_HT_2S ; 
 int /*<<< orphan*/  RTW_RATE_SECTION_OFDM ; 
 int /*<<< orphan*/  RTW_RATE_SECTION_VHT_1S ; 
 int /*<<< orphan*/  RTW_RATE_SECTION_VHT_2S ; 
 scalar_t__ RTW_RF_PATH_MAX ; 
 int /*<<< orphan*/  rtw_cck_rates ; 
 int /*<<< orphan*/  rtw_cck_size ; 
 int /*<<< orphan*/  rtw_ht_1s_rates ; 
 int /*<<< orphan*/  rtw_ht_1s_size ; 
 int /*<<< orphan*/  rtw_ht_2s_rates ; 
 int /*<<< orphan*/  rtw_ht_2s_size ; 
 int /*<<< orphan*/  rtw_ofdm_rates ; 
 int /*<<< orphan*/  rtw_ofdm_size ; 
 int /*<<< orphan*/  rtw_phy_tx_power_by_rate_config_by_path (struct rtw_hal*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_vht_1s_rates ; 
 int /*<<< orphan*/  rtw_vht_1s_size ; 
 int /*<<< orphan*/  rtw_vht_2s_rates ; 
 int /*<<< orphan*/  rtw_vht_2s_size ; 

void rtw_phy_tx_power_by_rate_config(struct rtw_hal *hal)
{
	u8 path;

	for (path = 0; path < RTW_RF_PATH_MAX; path++) {
		rtw_phy_tx_power_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_CCK,
				rtw_cck_size, rtw_cck_rates);
		rtw_phy_tx_power_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_OFDM,
				rtw_ofdm_size, rtw_ofdm_rates);
		rtw_phy_tx_power_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_HT_1S,
				rtw_ht_1s_size, rtw_ht_1s_rates);
		rtw_phy_tx_power_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_HT_2S,
				rtw_ht_2s_size, rtw_ht_2s_rates);
		rtw_phy_tx_power_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_VHT_1S,
				rtw_vht_1s_size, rtw_vht_1s_rates);
		rtw_phy_tx_power_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_VHT_2S,
				rtw_vht_2s_size, rtw_vht_2s_rates);
	}
}