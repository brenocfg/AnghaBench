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
typedef  int u16 ;
struct rtw_dpk_info {scalar_t__ dpk_bw; int* dpk_gs; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BIT_BYPASS_DPD ; 
 int /*<<< orphan*/  BIT_DPD_CLK ; 
 int /*<<< orphan*/  BIT_DPD_EN ; 
 int /*<<< orphan*/  BIT_GS_PWSF ; 
 int /*<<< orphan*/  BIT_INNER_LB ; 
 int /*<<< orphan*/  BIT_IQ_SWITCH ; 
 int /*<<< orphan*/  BIT_RPT_DGAIN ; 
 int /*<<< orphan*/  BIT_RPT_SEL ; 
 int /*<<< orphan*/  BIT_SUBPAGE ; 
 int /*<<< orphan*/  BIT_TX_CFIR ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 scalar_t__ DPK_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 int /*<<< orphan*/  REG_DPD_CTL0 ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S0 ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S1 ; 
 int /*<<< orphan*/  REG_DPD_CTL15 ; 
 int /*<<< orphan*/  REG_DPD_CTL16 ; 
 int /*<<< orphan*/  REG_DPD_CTL1_S0 ; 
 int /*<<< orphan*/  REG_DPD_CTL1_S1 ; 
 int /*<<< orphan*/  REG_IQK_CTL1 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int /*<<< orphan*/  REG_RXSRAM_CTL ; 
 int /*<<< orphan*/  REG_R_CONFIG ; 
 int /*<<< orphan*/  REG_STAT_RPT ; 
 int RF_PATH_A ; 
 int /*<<< orphan*/  RTW_DPK_CAL_PWR ; 
 int /*<<< orphan*/  rtw8822c_dpk_one_shot (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dpk_cal_gs(struct rtw_dev *rtwdev, u8 path)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 tmp_gs = 0;

	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));
	rtw_write32_mask(rtwdev, REG_IQK_CTL1, BIT_BYPASS_DPD, 0x0);
	rtw_write32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);
	rtw_write32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x9);
	rtw_write32_mask(rtwdev, REG_R_CONFIG, BIT_INNER_LB, 0x1);
	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_write32_mask(rtwdev, REG_RXSRAM_CTL, BIT_DPD_CLK, 0xf);

	if (path == RF_PATH_A) {
		rtw_write32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF,
				 0x1066680);
		rtw_write32_mask(rtwdev, REG_DPD_CTL1_S0, BIT_DPD_EN, 0x1);
	} else {
		rtw_write32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF,
				 0x1066680);
		rtw_write32_mask(rtwdev, REG_DPD_CTL1_S1, BIT_DPD_EN, 0x1);
	}

	if (dpk_info->dpk_bw == DPK_CHANNEL_WIDTH_80) {
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x80001310);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x00001310);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x810000db);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x010000db);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x0000b428);
		rtw_write32(rtwdev, REG_DPD_CTL15,
			    0x05020000 | (BIT(path) << 28));
	} else {
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x8200190c);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x0200190c);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x8301ee14);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x0301ee14);
		rtw_write32(rtwdev, REG_DPD_CTL16, 0x0000b428);
		rtw_write32(rtwdev, REG_DPD_CTL15,
			    0x05020008 | (BIT(path) << 28));
	}

	rtw_write32_mask(rtwdev, REG_DPD_CTL0, MASKBYTE3, 0x8 | path);

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_CAL_PWR);

	rtw_write32_mask(rtwdev, REG_DPD_CTL15, MASKBYTE3, 0x0);
	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));
	rtw_write32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x0);
	rtw_write32_mask(rtwdev, REG_R_CONFIG, BIT_INNER_LB, 0x0);
	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);

	if (path == RF_PATH_A)
		rtw_write32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF, 0x5b);
	else
		rtw_write32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF, 0x5b);

	rtw_write32_mask(rtwdev, REG_RXSRAM_CTL, BIT_RPT_SEL, 0x0);

	tmp_gs = (u16)rtw_read32_mask(rtwdev, REG_STAT_RPT, BIT_RPT_DGAIN);
	tmp_gs = (tmp_gs * 910) >> 10;
	tmp_gs = DIV_ROUND_CLOSEST(tmp_gs, 10);

	if (path == RF_PATH_A)
		rtw_write32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF, tmp_gs);
	else
		rtw_write32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF, tmp_gs);

	dpk_info->dpk_gs[path] = tmp_gs;
}