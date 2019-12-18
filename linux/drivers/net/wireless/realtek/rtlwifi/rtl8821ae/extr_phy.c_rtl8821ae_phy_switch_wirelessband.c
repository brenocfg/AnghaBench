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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * ofdm_index; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_hal {scalar_t__ current_bandtype; scalar_t__ hw_type; } ;
struct rtl_dm {int swing_diff_2g; int swing_diff_5g; int default_ofdm_index; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;
typedef  enum band_type { ____Placeholder_band_type } band_type ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 int BCCKEN ; 
 int BOFDMEN ; 
 int /*<<< orphan*/  COMP_MLME ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ HARDWARE_TYPE_RTL8821AE ; 
 int RA_RFE_PINMUX ; 
 int RA_TXSCALE ; 
 int RB_TXSCALE ; 
 int RCCK_RX ; 
 int /*<<< orphan*/  REG_CCK_CHECK ; 
 int /*<<< orphan*/  REG_TXPKT_EMPTY ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 int ROFDMCCKEN ; 
 int RTXPATH ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8812ae_phy_set_rfe_reg_24g (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8812ae_phy_set_rfe_reg_5g (struct ieee80211_hw*) ; 
 int phy_get_tx_swing_8812A (struct ieee80211_hw*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  rtl8821ae_dm_clear_txpower_tracking_state (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_phy_query_bb_reg (struct ieee80211_hw*,int,int) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_word (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl8821ae_phy_switch_wirelessband(struct ieee80211_hw *hw, u8 band)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_dm *rtldm = rtl_dm(rtlpriv);
	u8 current_band = rtlhal->current_bandtype;
	u32 txpath, rxpath;
	s8 bb_diff_between_band;

	txpath = rtl8821ae_phy_query_bb_reg(hw, RTXPATH, 0xf0);
	rxpath = rtl8821ae_phy_query_bb_reg(hw, RCCK_RX, 0x0f000000);
	rtlhal->current_bandtype = (enum band_type) band;
	/* reconfig BB/RF according to wireless mode */
	if (rtlhal->current_bandtype == BAND_ON_2_4G) {
		/* BB & RF Config */
		rtl_set_bbreg(hw, ROFDMCCKEN, BOFDMEN|BCCKEN, 0x03);

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
			/* 0xCB0[15:12] = 0x7 (LNA_On)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF000, 0x7);
			/* 0xCB0[7:4] = 0x7 (PAPE_A)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF0, 0x7);
		}

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			/*0x834[1:0] = 0x1*/
			rtl_set_bbreg(hw, 0x834, 0x3, 0x1);
		}

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
			/* 0xC1C[11:8] = 0 */
			rtl_set_bbreg(hw, RA_TXSCALE, 0xF00, 0);
		} else {
			/* 0x82C[1:0] = 2b'00 */
			rtl_set_bbreg(hw, 0x82c, 0x3, 0);
		}

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			_rtl8812ae_phy_set_rfe_reg_24g(hw);

		rtl_set_bbreg(hw, RTXPATH, 0xf0, 0x1);
		rtl_set_bbreg(hw, RCCK_RX, 0x0f000000, 0x1);

		rtl_write_byte(rtlpriv, REG_CCK_CHECK, 0x0);
	} else {/* 5G band */
		u16 count, reg_41a;

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
			/*0xCB0[15:12] = 0x5 (LNA_On)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF000, 0x5);
			/*0xCB0[7:4] = 0x4 (PAPE_A)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF0, 0x4);
		}
		/*CCK_CHECK_en*/
		rtl_write_byte(rtlpriv, REG_CCK_CHECK, 0x80);

		count = 0;
		reg_41a = rtl_read_word(rtlpriv, REG_TXPKT_EMPTY);
		RT_TRACE(rtlpriv, COMP_SCAN, DBG_LOUD,
			 "Reg41A value %d\n", reg_41a);
		reg_41a &= 0x30;
		while ((reg_41a != 0x30) && (count < 50)) {
			udelay(50);
			RT_TRACE(rtlpriv, COMP_SCAN, DBG_LOUD, "Delay 50us\n");

			reg_41a = rtl_read_word(rtlpriv, REG_TXPKT_EMPTY);
			reg_41a &= 0x30;
			count++;
			RT_TRACE(rtlpriv, COMP_SCAN, DBG_LOUD,
				 "Reg41A value %d\n", reg_41a);
		}
		if (count != 0)
			RT_TRACE(rtlpriv, COMP_MLME, DBG_LOUD,
				 "PHY_SwitchWirelessBand8812(): Switch to 5G Band. Count = %d reg41A=0x%x\n",
				 count, reg_41a);

		/* 2012/02/01, Sinda add registry to switch workaround
		without long-run verification for scan issue. */
		rtl_set_bbreg(hw, ROFDMCCKEN, BOFDMEN|BCCKEN, 0x03);

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			/*0x834[1:0] = 0x2*/
			rtl_set_bbreg(hw, 0x834, 0x3, 0x2);
		}

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
			/* AGC table select */
			/* 0xC1C[11:8] = 1*/
			rtl_set_bbreg(hw, RA_TXSCALE, 0xF00, 1);
		} else
			/* 0x82C[1:0] = 2'b00 */
			rtl_set_bbreg(hw, 0x82c, 0x3, 1);

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			_rtl8812ae_phy_set_rfe_reg_5g(hw);

		rtl_set_bbreg(hw, RTXPATH, 0xf0, 0);
		rtl_set_bbreg(hw, RCCK_RX, 0x0f000000, 0xf);

		RT_TRACE(rtlpriv, COMP_SCAN, DBG_LOUD,
			 "==>PHY_SwitchWirelessBand8812() BAND_ON_5G settings OFDM index 0x%x\n",
			 rtlpriv->dm.ofdm_index[RF90_PATH_A]);
	}

	if ((rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) ||
	    (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)) {
		/* 0xC1C[31:21] */
		rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
			      phy_get_tx_swing_8812A(hw, band, RF90_PATH_A));
		/* 0xE1C[31:21] */
		rtl_set_bbreg(hw, RB_TXSCALE, 0xFFE00000,
			      phy_get_tx_swing_8812A(hw, band, RF90_PATH_B));

		/* <20121005, Kordan> When TxPowerTrack is ON,
		 *	we should take care of the change of BB swing.
		 *   That is, reset all info to trigger Tx power tracking.
		 */
		if (band != current_band) {
			bb_diff_between_band =
				(rtldm->swing_diff_2g - rtldm->swing_diff_5g);
			bb_diff_between_band = (band == BAND_ON_2_4G) ?
						bb_diff_between_band :
						(-1 * bb_diff_between_band);
			rtldm->default_ofdm_index += bb_diff_between_band * 2;
		}
		rtl8821ae_dm_clear_txpower_tracking_state(hw);
	}

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE,
		 "<==rtl8821ae_phy_switch_wirelessband():Switch Band OK.\n");
	return;
}