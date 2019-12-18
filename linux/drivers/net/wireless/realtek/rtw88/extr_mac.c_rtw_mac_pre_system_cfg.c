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

/* Variables and functions */
 int /*<<< orphan*/  BIT_BT_DIG_CLK_EN ; 
 int BIT_FEN_BB_GLB_RST ; 
 int BIT_FEN_BB_RSTB ; 
 int BIT_LNAON_SEL_EN ; 
 int BIT_LNAON_WLBT_SEL ; 
 int BIT_PAPE_SEL_EN ; 
 int BIT_PAPE_WLBT_SEL ; 
 int BIT_RF_EN ; 
 int BIT_RF_RSTB ; 
 int BIT_RF_SDM_RSTB ; 
 int BIT_WLRF1_BBRF_EN ; 
 int BIT_WLRFE_4_5_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int /*<<< orphan*/  REG_HCI_OPT_CTRL ; 
 int /*<<< orphan*/  REG_LED_CFG ; 
 int /*<<< orphan*/  REG_PAD_CTRL1 ; 
 int /*<<< orphan*/  REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_RSV_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_WLRF1 ; 
#define  RTW_HCI_TYPE_PCIE 129 
#define  RTW_HCI_TYPE_USB 128 
 int rtw_hci_type (struct rtw_dev*) ; 
 int rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtw_mac_pre_system_cfg(struct rtw_dev *rtwdev)
{
	u32 value32;
	u8 value8;

	rtw_write8(rtwdev, REG_RSV_CTRL, 0);

	switch (rtw_hci_type(rtwdev)) {
	case RTW_HCI_TYPE_PCIE:
		rtw_write32_set(rtwdev, REG_HCI_OPT_CTRL, BIT_BT_DIG_CLK_EN);
		break;
	case RTW_HCI_TYPE_USB:
		break;
	default:
		return -EINVAL;
	}

	/* config PIN Mux */
	value32 = rtw_read32(rtwdev, REG_PAD_CTRL1);
	value32 |= BIT_PAPE_WLBT_SEL | BIT_LNAON_WLBT_SEL;
	rtw_write32(rtwdev, REG_PAD_CTRL1, value32);

	value32 = rtw_read32(rtwdev, REG_LED_CFG);
	value32 &= ~(BIT_PAPE_SEL_EN | BIT_LNAON_SEL_EN);
	rtw_write32(rtwdev, REG_LED_CFG, value32);

	value32 = rtw_read32(rtwdev, REG_GPIO_MUXCFG);
	value32 |= BIT_WLRFE_4_5_EN;
	rtw_write32(rtwdev, REG_GPIO_MUXCFG, value32);

	/* disable BB/RF */
	value8 = rtw_read8(rtwdev, REG_SYS_FUNC_EN);
	value8 &= ~(BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST);
	rtw_write8(rtwdev, REG_SYS_FUNC_EN, value8);

	value8 = rtw_read8(rtwdev, REG_RF_CTRL);
	value8 &= ~(BIT_RF_SDM_RSTB | BIT_RF_RSTB | BIT_RF_EN);
	rtw_write8(rtwdev, REG_RF_CTRL, value8);

	value32 = rtw_read32(rtwdev, REG_WLRF1);
	value32 &= ~BIT_WLRF1_BBRF_EN;
	rtw_write32(rtwdev, REG_WLRF1, value32);

	return 0;
}