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
typedef  int u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  REG_RXSRAM_CTL ; 
 int /*<<< orphan*/  REG_STAT_RPT ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 rtw8822c_dpk_dc_corr_check(struct rtw_dev *rtwdev, u8 path)
{
	u16 dc_i, dc_q;
	u8 corr_val, corr_idx;

	rtw_write32(rtwdev, REG_RXSRAM_CTL, 0x000900f0);
	dc_i = (u16)rtw_read32_mask(rtwdev, REG_STAT_RPT, GENMASK(27, 16));
	dc_q = (u16)rtw_read32_mask(rtwdev, REG_STAT_RPT, GENMASK(11, 0));

	if (dc_i & BIT(11))
		dc_i = 0x1000 - dc_i;
	if (dc_q & BIT(11))
		dc_q = 0x1000 - dc_q;

	rtw_write32(rtwdev, REG_RXSRAM_CTL, 0x000000f0);
	corr_idx = (u8)rtw_read32_mask(rtwdev, REG_STAT_RPT, GENMASK(7, 0));
	corr_val = (u8)rtw_read32_mask(rtwdev, REG_STAT_RPT, GENMASK(15, 8));

	if (dc_i > 200 || dc_q > 200 || corr_idx < 40 || corr_idx > 65)
		return 1;
	else
		return 0;

}