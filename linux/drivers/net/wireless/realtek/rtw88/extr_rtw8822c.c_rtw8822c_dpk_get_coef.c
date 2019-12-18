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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  REG_DPD_CTL0 ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S0 ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S1 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 scalar_t__ RF_PATH_A ; 
 scalar_t__ RF_PATH_B ; 
 int /*<<< orphan*/  rtw8822c_dpk_coef_tbl_apply (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dpk_get_coef(struct rtw_dev *rtwdev, u8 path)
{
	rtw_write32(rtwdev, REG_NCTL0, 0x0000000c);

	if (path == RF_PATH_A) {
		rtw_write32_mask(rtwdev, REG_DPD_CTL0, BIT(24), 0x0);
		rtw_write32(rtwdev, REG_DPD_CTL0_S0, 0x30000080);
	} else if (path == RF_PATH_B) {
		rtw_write32_mask(rtwdev, REG_DPD_CTL0, BIT(24), 0x1);
		rtw_write32(rtwdev, REG_DPD_CTL0_S1, 0x30000080);
	}

	rtw8822c_dpk_coef_tbl_apply(rtwdev, path);
}