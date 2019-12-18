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
typedef  int u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_EN_BCN_FUNCTION ; 
 int /*<<< orphan*/  BIT_EN_EOF_V1 ; 
 int BIT_PRE_TX_CMD ; 
 int BIT_SIFS_BK_EN ; 
 int BIT_TSFT_SEL_TIMER0 ; 
 int /*<<< orphan*/  FAST_EDCA_BE_TH ; 
 int /*<<< orphan*/  FAST_EDCA_BK_TH ; 
 int /*<<< orphan*/  FAST_EDCA_VI_TH ; 
 int /*<<< orphan*/  FAST_EDCA_VO_TH ; 
 scalar_t__ REG_AMPDU_MAX_TIME_V1 ; 
 scalar_t__ REG_BAR_MODE_CTRL ; 
 scalar_t__ REG_BCNDMATIM ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 scalar_t__ REG_DRVERLYINT ; 
 scalar_t__ REG_EDCA_VI_PARAM ; 
 scalar_t__ REG_EDCA_VO_PARAM ; 
 scalar_t__ REG_FAST_EDCA_BEBK_SETTING ; 
 scalar_t__ REG_FAST_EDCA_VOVI_SETTING ; 
 scalar_t__ REG_PIFS ; 
 scalar_t__ REG_PROT_MODE_CTRL ; 
 scalar_t__ REG_RCR ; 
 scalar_t__ REG_RD_NAV_NXT ; 
 scalar_t__ REG_RXFLTMAP0 ; 
 scalar_t__ REG_RXFLTMAP2 ; 
 scalar_t__ REG_RXTSF_OFFSET_CCK ; 
 scalar_t__ REG_RX_PKT_LIMIT ; 
 scalar_t__ REG_SIFS ; 
 scalar_t__ REG_SLOT ; 
 scalar_t__ REG_SW_AMPDU_BURST_MODE_CTRL ; 
 scalar_t__ REG_TBTT_PROHIBIT ; 
 scalar_t__ REG_TCR ; 
 scalar_t__ REG_TIMER0_SRC_SEL ; 
 scalar_t__ REG_TXPAUSE ; 
 int /*<<< orphan*/  REG_TX_HANG_CTRL ; 
 scalar_t__ REG_TX_PTCL_CTRL ; 
 scalar_t__ REG_WMAC_OPTION_FUNCTION ; 
 int /*<<< orphan*/  WLAN_AMPDU_MAX_TIME ; 
 int WLAN_BAR_RETRY_LIMIT ; 
 int /*<<< orphan*/  WLAN_BCN_DMA_TIME ; 
 int /*<<< orphan*/  WLAN_DRV_EARLY_INT ; 
 int WLAN_MAC_OPT_FUNC2 ; 
 int /*<<< orphan*/  WLAN_MAC_OPT_NORM_FUNC1 ; 
 int WLAN_MAX_AGG_PKT_LIMIT ; 
 int WLAN_NAV_CFG ; 
 int /*<<< orphan*/  WLAN_PIFS_TIME ; 
 int WLAN_RA_TRY_RATE_AGG_LIMIT ; 
 int WLAN_RCR_CFG ; 
 int WLAN_RTS_LEN_TH ; 
 int WLAN_RTS_MAX_AGG_PKT_LIMIT ; 
 int WLAN_RTS_TX_TIME_TH ; 
 int /*<<< orphan*/  WLAN_RXPKT_MAX_SZ_512 ; 
 int WLAN_RX_FILTER0 ; 
 int WLAN_RX_FILTER2 ; 
 int WLAN_RX_TSF_CFG ; 
 int WLAN_SIFS_CFG ; 
 int /*<<< orphan*/  WLAN_SLOT_TIME ; 
 int WLAN_TBTT_TIME ; 
 int /*<<< orphan*/  WLAN_TX_FUNC_CFG1 ; 
 int /*<<< orphan*/  WLAN_TX_FUNC_CFG2 ; 
 int WLAN_VI_TXOP_LIMIT ; 
 int WLAN_VO_TXOP_LIMIT ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_clr (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw8822b_mac_init(struct rtw_dev *rtwdev)
{
	u32 value32;

	/* protocol configuration */
	rtw_write8_clr(rtwdev, REG_SW_AMPDU_BURST_MODE_CTRL, BIT_PRE_TX_CMD);
	rtw_write8(rtwdev, REG_AMPDU_MAX_TIME_V1, WLAN_AMPDU_MAX_TIME);
	rtw_write8_set(rtwdev, REG_TX_HANG_CTRL, BIT_EN_EOF_V1);
	value32 = WLAN_RTS_LEN_TH | (WLAN_RTS_TX_TIME_TH << 8) |
		  (WLAN_MAX_AGG_PKT_LIMIT << 16) |
		  (WLAN_RTS_MAX_AGG_PKT_LIMIT << 24);
	rtw_write32(rtwdev, REG_PROT_MODE_CTRL, value32);
	rtw_write16(rtwdev, REG_BAR_MODE_CTRL + 2,
		    WLAN_BAR_RETRY_LIMIT | WLAN_RA_TRY_RATE_AGG_LIMIT << 8);
	rtw_write8(rtwdev, REG_FAST_EDCA_VOVI_SETTING, FAST_EDCA_VO_TH);
	rtw_write8(rtwdev, REG_FAST_EDCA_VOVI_SETTING + 2, FAST_EDCA_VI_TH);
	rtw_write8(rtwdev, REG_FAST_EDCA_BEBK_SETTING, FAST_EDCA_BE_TH);
	rtw_write8(rtwdev, REG_FAST_EDCA_BEBK_SETTING + 2, FAST_EDCA_BK_TH);
	/* EDCA configuration */
	rtw_write8_clr(rtwdev, REG_TIMER0_SRC_SEL, BIT_TSFT_SEL_TIMER0);
	rtw_write16(rtwdev, REG_TXPAUSE, 0x0000);
	rtw_write8(rtwdev, REG_SLOT, WLAN_SLOT_TIME);
	rtw_write8(rtwdev, REG_PIFS, WLAN_PIFS_TIME);
	rtw_write32(rtwdev, REG_SIFS, WLAN_SIFS_CFG);
	rtw_write16(rtwdev, REG_EDCA_VO_PARAM + 2, WLAN_VO_TXOP_LIMIT);
	rtw_write16(rtwdev, REG_EDCA_VI_PARAM + 2, WLAN_VI_TXOP_LIMIT);
	rtw_write32(rtwdev, REG_RD_NAV_NXT, WLAN_NAV_CFG);
	rtw_write16(rtwdev, REG_RXTSF_OFFSET_CCK, WLAN_RX_TSF_CFG);
	/* Set beacon cotnrol - enable TSF and other related functions */
	rtw_write8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);
	/* Set send beacon related registers */
	rtw_write32(rtwdev, REG_TBTT_PROHIBIT, WLAN_TBTT_TIME);
	rtw_write8(rtwdev, REG_DRVERLYINT, WLAN_DRV_EARLY_INT);
	rtw_write8(rtwdev, REG_BCNDMATIM, WLAN_BCN_DMA_TIME);
	rtw_write8_clr(rtwdev, REG_TX_PTCL_CTRL + 1, BIT_SIFS_BK_EN >> 8);
	/* WMAC configuration */
	rtw_write32(rtwdev, REG_RXFLTMAP0, WLAN_RX_FILTER0);
	rtw_write16(rtwdev, REG_RXFLTMAP2, WLAN_RX_FILTER2);
	rtw_write32(rtwdev, REG_RCR, WLAN_RCR_CFG);
	rtw_write8(rtwdev, REG_RX_PKT_LIMIT, WLAN_RXPKT_MAX_SZ_512);
	rtw_write8(rtwdev, REG_TCR + 2, WLAN_TX_FUNC_CFG2);
	rtw_write8(rtwdev, REG_TCR + 1, WLAN_TX_FUNC_CFG1);
	rtw_write32(rtwdev, REG_WMAC_OPTION_FUNCTION + 8, WLAN_MAC_OPT_FUNC2);
	rtw_write8(rtwdev, REG_WMAC_OPTION_FUNCTION + 4, WLAN_MAC_OPT_NORM_FUNC1);

	return 0;
}