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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_BTCCA_CTRL ; 
 int /*<<< orphan*/  BIT_BT_AOD_GPIO3 ; 
 int /*<<< orphan*/  BIT_BT_PTA_EN ; 
 int BIT_EN_BCN_FUNCTION ; 
 int BIT_GNT_BT_POLARITY ; 
 int /*<<< orphan*/  BIT_PTA_EDCCA_EN ; 
 int BIT_PTA_WL_TX_EN ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int /*<<< orphan*/  REG_BT_COEX_V2 ; 
 int /*<<< orphan*/  REG_BT_STAT_CTRL ; 
 int /*<<< orphan*/  REG_BT_TDMA_TIME ; 
 int /*<<< orphan*/  REG_DUMMY_PAGE4_V1 ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int /*<<< orphan*/  REG_QUEUE_CTRL ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8_clr (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void rtw8822c_coex_cfg_init(struct rtw_dev *rtwdev)
{
	/* enable TBTT nterrupt */
	rtw_write8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);

	/* BT report packet sample rate	 */
	/* 0x790[5:0]=0x5 */
	rtw_write8_set(rtwdev, REG_BT_TDMA_TIME, 0x05);

	/* enable BT counter statistics */
	rtw_write8(rtwdev, REG_BT_STAT_CTRL, 0x1);

	/* enable PTA (3-wire function form BT side) */
	rtw_write32_set(rtwdev, REG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	rtw_write32_set(rtwdev, REG_GPIO_MUXCFG, BIT_BT_AOD_GPIO3);

	/* enable PTA (tx/rx signal form WiFi side) */
	rtw_write8_set(rtwdev, REG_QUEUE_CTRL, BIT_PTA_WL_TX_EN);
	/* wl tx signal to PTA not case EDCCA */
	rtw_write8_clr(rtwdev, REG_QUEUE_CTRL, BIT_PTA_EDCCA_EN);
	/* GNT_BT=1 while select both */
	rtw_write8_set(rtwdev, REG_BT_COEX_V2, BIT_GNT_BT_POLARITY);
	/* BT_CCA = ~GNT_WL_BB, (not or GNT_BT_BB, LTE_Rx */
	rtw_write8_clr(rtwdev, REG_DUMMY_PAGE4_V1, BIT_BTCCA_CTRL);

	/* to avoid RF parameter error */
	rtw_write_rf(rtwdev, RF_PATH_B, 0x1, 0xfffff, 0x40000);
}