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
typedef  int u8 ;
typedef  int u32 ;
struct rtw_dpk_info {int* result; int /*<<< orphan*/ * dpk_txagc; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SUBPAGE ; 
 int /*<<< orphan*/  REG_DPD_AGC ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int /*<<< orphan*/  rtw8822c_dpk_coef_write (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dpk_fill_result(struct rtw_dev *rtwdev, u32 dpk_txagc,
				     u8 path, u8 result)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));

	if (result)
		rtw_write8(rtwdev, REG_DPD_AGC, (u8)(dpk_txagc - 6));
	else
		rtw_write8(rtwdev, REG_DPD_AGC, 0x00);

	dpk_info->result[path] = result;
	dpk_info->dpk_txagc[path] = rtw_read8(rtwdev, REG_DPD_AGC);

	rtw8822c_dpk_coef_write(rtwdev, path, result);
}