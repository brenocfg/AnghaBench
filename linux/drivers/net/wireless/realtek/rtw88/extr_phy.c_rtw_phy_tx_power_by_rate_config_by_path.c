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
struct rtw_hal {void*** tx_pwr_by_rate_offset_5g; void*** tx_pwr_by_rate_offset_2g; void*** tx_pwr_by_rate_base_5g; void*** tx_pwr_by_rate_base_2g; } ;
typedef  void* s8 ;

/* Variables and functions */
 size_t RTW_RATE_SECTION_VHT_1S ; 

__attribute__((used)) static void
rtw_phy_tx_power_by_rate_config_by_path(struct rtw_hal *hal, u8 path,
					u8 rs, u8 size, u8 *rates)
{
	u8 rate;
	u8 base_idx, rate_idx;
	s8 base_2g, base_5g;

	if (rs >= RTW_RATE_SECTION_VHT_1S)
		base_idx = rates[size - 3];
	else
		base_idx = rates[size - 1];
	base_2g = hal->tx_pwr_by_rate_offset_2g[path][base_idx];
	base_5g = hal->tx_pwr_by_rate_offset_5g[path][base_idx];
	hal->tx_pwr_by_rate_base_2g[path][rs] = base_2g;
	hal->tx_pwr_by_rate_base_5g[path][rs] = base_5g;
	for (rate = 0; rate < size; rate++) {
		rate_idx = rates[rate];
		hal->tx_pwr_by_rate_offset_2g[path][rate_idx] -= base_2g;
		hal->tx_pwr_by_rate_offset_5g[path][rate_idx] -= base_5g;
	}
}