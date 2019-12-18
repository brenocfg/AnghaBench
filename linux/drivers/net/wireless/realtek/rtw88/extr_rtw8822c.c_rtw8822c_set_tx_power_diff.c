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
typedef  int u8 ;
typedef  int u32 ;
struct rtw_dev {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_set_tx_power_diff(struct rtw_dev *rtwdev, u8 rate,
				       s8 *diff_idx)
{
	u32 offset_txagc = 0x3a00;
	u8 rate_idx = rate & 0xfc;
	u8 pwr_idx[4];
	u32 phy_pwr_idx;
	int i;

	for (i = 0; i < 4; i++)
		pwr_idx[i] = diff_idx[i] & 0x7f;

	phy_pwr_idx = pwr_idx[0] |
		      (pwr_idx[1] << 8) |
		      (pwr_idx[2] << 16) |
		      (pwr_idx[3] << 24);

	rtw_write32_mask(rtwdev, 0x1c90, BIT(15), 0x0);
	rtw_write32_mask(rtwdev, offset_txagc + rate_idx, MASKDWORD,
			 phy_pwr_idx);
}