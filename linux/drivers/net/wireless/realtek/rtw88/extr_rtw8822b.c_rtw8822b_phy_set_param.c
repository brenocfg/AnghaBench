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
struct TYPE_2__ {int crystal_cap; } ;
struct rtw_dev {TYPE_1__ efuse; struct rtw_hal hal; } ;

/* Variables and functions */
 int BIT_FEN_BB_GLB_RST ; 
 int BIT_FEN_BB_RSTB ; 
 int BIT_RF_EN ; 
 int BIT_RF_RSTB ; 
 int BIT_RF_SDM_RSTB ; 
 int /*<<< orphan*/  BIT_RX_PSEL_RST ; 
 int /*<<< orphan*/  BIT_WLRF1_BBRF_EN ; 
 int /*<<< orphan*/  REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_RXPSEL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_WLRF1 ; 
 int /*<<< orphan*/  rtw8822b_config_trx_mode (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw8822b_phy_rfe_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_phy_load_tables (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write32_clr (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822b_phy_set_param(struct rtw_dev *rtwdev)
{
	struct rtw_hal *hal = &rtwdev->hal;
	u8 crystal_cap;
	bool is_tx2_path;

	/* power on BB/RF domain */
	rtw_write8_set(rtwdev, REG_SYS_FUNC_EN,
		       BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST);
	rtw_write8_set(rtwdev, REG_RF_CTRL,
		       BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	rtw_write32_set(rtwdev, REG_WLRF1, BIT_WLRF1_BBRF_EN);

	/* pre init before header files config */
	rtw_write32_clr(rtwdev, REG_RXPSEL, BIT_RX_PSEL_RST);

	rtw_phy_load_tables(rtwdev);

	crystal_cap = rtwdev->efuse.crystal_cap & 0x3F;
	rtw_write32_mask(rtwdev, 0x24, 0x7e000000, crystal_cap);
	rtw_write32_mask(rtwdev, 0x28, 0x7e, crystal_cap);

	/* post init after header files config */
	rtw_write32_set(rtwdev, REG_RXPSEL, BIT_RX_PSEL_RST);

	is_tx2_path = false;
	rtw8822b_config_trx_mode(rtwdev, hal->antenna_tx, hal->antenna_rx,
				 is_tx2_path);
	rtw_phy_init(rtwdev);

	rtw8822b_phy_rfe_init(rtwdev);
}