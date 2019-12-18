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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct rtw_dev {int dummy; } ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {int /*<<< orphan*/  mask_cs; int /*<<< orphan*/  reg_cs; int /*<<< orphan*/  mask_pd; int /*<<< orphan*/  reg_pd; } ;

/* Variables and functions */
 scalar_t__ RTW_CCK_CS_ERR1 ; 
 scalar_t__ RTW_CCK_CS_ERR2 ; 
 scalar_t__ RTW_CCK_CS_MAX ; 
 scalar_t__ RTW_CCK_PD_MAX ; 
 size_t RTW_CHANNEL_WIDTH_40 ; 
 size_t RTW_RF_PATH_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__** rtw8822c_cck_pd_reg ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
rtw8822c_phy_cck_pd_set_reg(struct rtw_dev *rtwdev,
			    s8 pd_diff, s8 cs_diff, u8 bw, u8 nrx)
{
	u32 pd, cs;

	if (WARN_ON(bw > RTW_CHANNEL_WIDTH_40 || nrx >= RTW_RF_PATH_MAX))
		return;

	pd = rtw_read32_mask(rtwdev,
			     rtw8822c_cck_pd_reg[bw][nrx].reg_pd,
			     rtw8822c_cck_pd_reg[bw][nrx].mask_pd);
	cs = rtw_read32_mask(rtwdev,
			     rtw8822c_cck_pd_reg[bw][nrx].reg_cs,
			     rtw8822c_cck_pd_reg[bw][nrx].mask_cs);
	pd += pd_diff;
	cs += cs_diff;
	if (pd > RTW_CCK_PD_MAX)
		pd = RTW_CCK_PD_MAX;
	if (cs == RTW_CCK_CS_ERR1 || cs == RTW_CCK_CS_ERR2)
		cs++;
	else if (cs > RTW_CCK_CS_MAX)
		cs = RTW_CCK_CS_MAX;
	rtw_write32_mask(rtwdev,
			 rtw8822c_cck_pd_reg[bw][nrx].reg_pd,
			 rtw8822c_cck_pd_reg[bw][nrx].mask_pd,
			 pd);
	rtw_write32_mask(rtwdev,
			 rtw8822c_cck_pd_reg[bw][nrx].reg_cs,
			 rtw8822c_cck_pd_reg[bw][nrx].mask_cs,
			 cs);
}