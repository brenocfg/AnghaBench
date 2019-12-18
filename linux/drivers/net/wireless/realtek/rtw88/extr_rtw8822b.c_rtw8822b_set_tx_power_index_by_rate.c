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
typedef  int u32 ;
struct rtw_hal {size_t** tx_pwr_tbl; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */
 size_t** rtw_rate_section ; 
 int* rtw_rate_size ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int const,int) ; 

__attribute__((used)) static void
rtw8822b_set_tx_power_index_by_rate(struct rtw_dev *rtwdev, u8 path, u8 rs)
{
	struct rtw_hal *hal = &rtwdev->hal;
	static const u32 offset_txagc[2] = {0x1d00, 0x1d80};
	static u32 phy_pwr_idx;
	u8 rate, rate_idx, pwr_index, shift;
	int j;

	for (j = 0; j < rtw_rate_size[rs]; j++) {
		rate = rtw_rate_section[rs][j];
		pwr_index = hal->tx_pwr_tbl[path][rate];
		shift = rate & 0x3;
		phy_pwr_idx |= ((u32)pwr_index << (shift * 8));
		if (shift == 0x3) {
			rate_idx = rate & 0xfc;
			rtw_write32(rtwdev, offset_txagc[path] + rate_idx,
				    phy_pwr_idx);
			phy_pwr_idx = 0;
		}
	}
}