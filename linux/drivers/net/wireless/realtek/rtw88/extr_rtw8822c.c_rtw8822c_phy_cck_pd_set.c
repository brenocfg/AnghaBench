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
struct rtw_dm_info {size_t** cck_pd_lv; int /*<<< orphan*/  cck_fa_avg; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_FA_AVG_RESET ; 
 int /*<<< orphan*/  rtw8822c_phy_cck_pd_set_reg (struct rtw_dev*,int,int,size_t,size_t) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822c_phy_cck_pd_set(struct rtw_dev *rtwdev, u8 new_lvl)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	s8 pd_lvl[4] = {2, 4, 6, 8};
	s8 cs_lvl[4] = {2, 2, 2, 4};
	u8 cur_lvl;
	u8 nrx, bw;

	nrx = (u8)rtw_read32_mask(rtwdev, 0x1a2c, 0x60000);
	bw = (u8)rtw_read32_mask(rtwdev, 0x9b0, 0xc);

	if (dm_info->cck_pd_lv[bw][nrx] == new_lvl)
		return;

	cur_lvl = dm_info->cck_pd_lv[bw][nrx];

	/* update cck pd info */
	dm_info->cck_fa_avg = CCK_FA_AVG_RESET;

	rtw8822c_phy_cck_pd_set_reg(rtwdev,
				    pd_lvl[new_lvl] - pd_lvl[cur_lvl],
				    cs_lvl[new_lvl] - cs_lvl[cur_lvl],
				    bw, nrx);
	dm_info->cck_pd_lv[bw][nrx] = new_lvl;
}