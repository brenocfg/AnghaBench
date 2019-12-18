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
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  BIT_SUBPAGE ; 
 int /*<<< orphan*/  REG_DPD_CTL1_S0 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int /*<<< orphan*/  RFREG_MASK ; 
 int /*<<< orphan*/  RF_MODE_TRXAGC ; 
 int /*<<< orphan*/  RTW_DPK_DO_DPK ; 
 int /*<<< orphan*/  rtw8822c_dpk_get_coef (struct rtw_dev*,int) ; 
 int rtw8822c_dpk_one_shot (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 rtw8822c_dpk_by_path(struct rtw_dev *rtwdev, u32 tx_agc, u8 path)
{
	u8 result;

	result = rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DO_DPK);

	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));

	result = result | (u8)rtw_read32_mask(rtwdev, REG_DPD_CTL1_S0, BIT(26));

	rtw_write_rf(rtwdev, path, RF_MODE_TRXAGC, RFREG_MASK, 0x33e14);

	rtw8822c_dpk_get_coef(rtwdev, path);

	return result;
}