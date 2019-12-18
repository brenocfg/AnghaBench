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
struct rtw_hal {int /*<<< orphan*/  antenna_rx; int /*<<< orphan*/  antenna_tx; } ;
struct rtw_dm_info {int cck_gi_u_bnd; int cck_gi_l_bnd; } ;
struct TYPE_2__ {int crystal_cap; } ;
struct rtw_dev {TYPE_1__ efuse; struct rtw_hal hal; struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 int BIT_FEN_BB_GLB_RST ; 
 int BIT_FEN_BB_RSTB ; 
 int BIT_RF_EN ; 
 int BIT_RF_RSTB ; 
 int BIT_RF_SDM_RSTB ; 
 int /*<<< orphan*/  BIT_WLRF1_BBRF_EN ; 
 int DIS_DPD_MASK ; 
 int DIS_DPD_RATEALL ; 
 int /*<<< orphan*/  REG_ANAPAR_XTAL_0 ; 
 int /*<<< orphan*/  REG_DIS_DPD ; 
 int /*<<< orphan*/  REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_WLRF1 ; 
 int /*<<< orphan*/  rtw8822c_config_trx_mode (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw8822c_header_file_init (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw8822c_rf_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_load_tables (struct rtw_dev*) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_phy_set_param(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	struct rtw_hal *hal = &rtwdev->hal;
	u8 crystal_cap;
	u8 cck_gi_u_bnd_msb = 0;
	u8 cck_gi_u_bnd_lsb = 0;
	u8 cck_gi_l_bnd_msb = 0;
	u8 cck_gi_l_bnd_lsb = 0;
	bool is_tx2_path;

	/* power on BB/RF domain */
	rtw_write8_set(rtwdev, REG_SYS_FUNC_EN,
		       BIT_FEN_BB_GLB_RST | BIT_FEN_BB_RSTB);
	rtw_write8_set(rtwdev, REG_RF_CTRL,
		       BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	rtw_write32_set(rtwdev, REG_WLRF1, BIT_WLRF1_BBRF_EN);

	/* disable low rate DPD */
	rtw_write32_mask(rtwdev, REG_DIS_DPD, DIS_DPD_MASK, DIS_DPD_RATEALL);

	/* pre init before header files config */
	rtw8822c_header_file_init(rtwdev, true);

	rtw_phy_load_tables(rtwdev);

	crystal_cap = rtwdev->efuse.crystal_cap & 0x7f;
	rtw_write32_mask(rtwdev, REG_ANAPAR_XTAL_0, 0xfffc00,
			 crystal_cap | (crystal_cap << 7));

	/* post init after header files config */
	rtw8822c_header_file_init(rtwdev, false);

	is_tx2_path = false;
	rtw8822c_config_trx_mode(rtwdev, hal->antenna_tx, hal->antenna_rx,
				 is_tx2_path);
	rtw_phy_init(rtwdev);

	cck_gi_u_bnd_msb = (u8)rtw_read32_mask(rtwdev, 0x1a98, 0xc000);
	cck_gi_u_bnd_lsb = (u8)rtw_read32_mask(rtwdev, 0x1aa8, 0xf0000);
	cck_gi_l_bnd_msb = (u8)rtw_read32_mask(rtwdev, 0x1a98, 0xc0);
	cck_gi_l_bnd_lsb = (u8)rtw_read32_mask(rtwdev, 0x1a70, 0x0f000000);

	dm_info->cck_gi_u_bnd = ((cck_gi_u_bnd_msb << 4) | (cck_gi_u_bnd_lsb));
	dm_info->cck_gi_l_bnd = ((cck_gi_l_bnd_msb << 4) | (cck_gi_l_bnd_lsb));

	rtw8822c_rf_init(rtwdev);
}