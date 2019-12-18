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
struct txpower_info_5g {int** index_bw40_base; int** bw40_diff; int** bw20_diff; int** ofdm_diff; } ;
struct txpower_info_2g {int** index_cck_base; int** index_bw40_base; int** bw40_diff; int** bw20_diff; int** ofdm_diff; int** cck_diff; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_TX_PWR_INX ; 
 int MAX_CHNL_GROUP_24G ; 
 int MAX_CHNL_GROUP_5G ; 
 int MAX_RF_PATH ; 
 int MAX_TX_COUNT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_24g_base (struct txpower_info_2g*,int) ; 

__attribute__((used)) static void read_power_value_fromprom(struct ieee80211_hw *hw,
				      struct txpower_info_2g *pwrinfo24g,
				      struct txpower_info_5g *pwrinfo5g,
				      bool autoload_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 rfpath, eeaddr = EEPROM_TX_PWR_INX, group, txcnt = 0;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "hal_ReadPowerValueFromPROM88E():PROMContent[0x%x]=0x%x\n",
		 (eeaddr+1), hwinfo[eeaddr+1]);
	if (0xFF == hwinfo[eeaddr+1])  /*YJ,add,120316*/
		autoload_fail = true;

	if (autoload_fail) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "auto load fail : Use Default value!\n");
		for (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) {
			/* 2.4G default value */
			set_24g_base(pwrinfo24g, rfpath);
		}
		return;
	}

	for (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) {
		/*2.4G default value*/
		for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
			pwrinfo24g->index_cck_base[rfpath][group] =
			  hwinfo[eeaddr++];
			if (pwrinfo24g->index_cck_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_cck_base[rfpath][group] =
				  0x2D;
		}
		for (group = 0 ; group < MAX_CHNL_GROUP_24G-1; group++) {
			pwrinfo24g->index_bw40_base[rfpath][group] =
				hwinfo[eeaddr++];
			if (pwrinfo24g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_bw40_base[rfpath][group] =
					0x2D;
		}
		pwrinfo24g->bw40_diff[rfpath][0] = 0;
		if (hwinfo[eeaddr] == 0xFF) {
			pwrinfo24g->bw20_diff[rfpath][0] = 0x02;
		} else {
			pwrinfo24g->bw20_diff[rfpath][0] =
				(hwinfo[eeaddr]&0xf0)>>4;
			/*bit sign number to 8 bit sign number*/
			if (pwrinfo24g->bw20_diff[rfpath][0] & BIT(3))
				pwrinfo24g->bw20_diff[rfpath][0] |= 0xF0;
		}

		if (hwinfo[eeaddr] == 0xFF) {
			pwrinfo24g->ofdm_diff[rfpath][0] = 0x04;
		} else {
			pwrinfo24g->ofdm_diff[rfpath][0] =
				(hwinfo[eeaddr]&0x0f);
				/*bit sign number to 8 bit sign number*/
			if (pwrinfo24g->ofdm_diff[rfpath][0] & BIT(3))
				pwrinfo24g->ofdm_diff[rfpath][0] |= 0xF0;
		}
		pwrinfo24g->cck_diff[rfpath][0] = 0;
		eeaddr++;
		for (txcnt = 1; txcnt < MAX_TX_COUNT; txcnt++) {
			if (hwinfo[eeaddr] == 0xFF) {
				pwrinfo24g->bw40_diff[rfpath][txcnt] = 0xFE;
			} else {
				pwrinfo24g->bw40_diff[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0xf0)>>4;
				if (pwrinfo24g->bw40_diff[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->bw40_diff[rfpath][txcnt] |=
					  0xF0;
			}

			if (hwinfo[eeaddr] == 0xFF) {
				pwrinfo24g->bw20_diff[rfpath][txcnt] =
					0xFE;
			} else {
				pwrinfo24g->bw20_diff[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0x0f);
				if (pwrinfo24g->bw20_diff[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->bw20_diff[rfpath][txcnt] |=
					  0xF0;
			}
			eeaddr++;

			if (hwinfo[eeaddr] == 0xFF) {
				pwrinfo24g->ofdm_diff[rfpath][txcnt] = 0xFE;
			} else {
				pwrinfo24g->ofdm_diff[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0xf0)>>4;
				if (pwrinfo24g->ofdm_diff[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->ofdm_diff[rfpath][txcnt] |=
					  0xF0;
			}

			if (hwinfo[eeaddr] == 0xFF) {
				pwrinfo24g->cck_diff[rfpath][txcnt] =	0xFE;
			} else {
				pwrinfo24g->cck_diff[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0x0f);
				if (pwrinfo24g->cck_diff[rfpath][txcnt] &
				    BIT(3))
					pwrinfo24g->cck_diff[rfpath][txcnt] |=
					  0xF0;
			}
			eeaddr++;
		}

		/*5G default value*/
		for (group = 0 ; group < MAX_CHNL_GROUP_5G; group++) {
			pwrinfo5g->index_bw40_base[rfpath][group] =
				hwinfo[eeaddr++];
			if (pwrinfo5g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo5g->index_bw40_base[rfpath][group] =
				  0xFE;
		}

		pwrinfo5g->bw40_diff[rfpath][0] = 0;

		if (hwinfo[eeaddr] == 0xFF) {
			pwrinfo5g->bw20_diff[rfpath][0] = 0;
		} else {
			pwrinfo5g->bw20_diff[rfpath][0] =
			  (hwinfo[eeaddr]&0xf0)>>4;
			if (pwrinfo5g->bw20_diff[rfpath][0] & BIT(3))
				pwrinfo5g->bw20_diff[rfpath][0] |= 0xF0;
		}

		if (hwinfo[eeaddr] == 0xFF) {
			pwrinfo5g->ofdm_diff[rfpath][0] = 0x04;
		} else {
			pwrinfo5g->ofdm_diff[rfpath][0] = (hwinfo[eeaddr]&0x0f);
			if (pwrinfo5g->ofdm_diff[rfpath][0] & BIT(3))
				pwrinfo5g->ofdm_diff[rfpath][0] |= 0xF0;
		}
		eeaddr++;
		for (txcnt = 1; txcnt < MAX_TX_COUNT; txcnt++) {
			if (hwinfo[eeaddr] == 0xFF) {
				pwrinfo5g->bw40_diff[rfpath][txcnt] =	0xFE;
			} else {
				pwrinfo5g->bw40_diff[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0xf0)>>4;
				if (pwrinfo5g->bw40_diff[rfpath][txcnt] &
				    BIT(3))
					pwrinfo5g->bw40_diff[rfpath][txcnt] |=
					  0xF0;
			}

			if (hwinfo[eeaddr] == 0xFF) {
				pwrinfo5g->bw20_diff[rfpath][txcnt] =	0xFE;
			} else {
				pwrinfo5g->bw20_diff[rfpath][txcnt] =
				  (hwinfo[eeaddr]&0x0f);
				if (pwrinfo5g->bw20_diff[rfpath][txcnt] &
				    BIT(3))
					pwrinfo5g->bw20_diff[rfpath][txcnt] |=
					  0xF0;
			}
			eeaddr++;
		}

		if (hwinfo[eeaddr] == 0xFF) {
			pwrinfo5g->ofdm_diff[rfpath][1] = 0xFE;
			pwrinfo5g->ofdm_diff[rfpath][2] = 0xFE;
		} else {
			pwrinfo5g->ofdm_diff[rfpath][1] =
					(hwinfo[eeaddr]&0xf0)>>4;
			pwrinfo5g->ofdm_diff[rfpath][2] =
					(hwinfo[eeaddr]&0x0f);
		}
		eeaddr++;

		if (hwinfo[eeaddr] == 0xFF)
			pwrinfo5g->ofdm_diff[rfpath][3] = 0xFE;
		else
			pwrinfo5g->ofdm_diff[rfpath][3] = (hwinfo[eeaddr]&0x0f);
		eeaddr++;

		for (txcnt = 1; txcnt < MAX_TX_COUNT; txcnt++) {
			if (pwrinfo5g->ofdm_diff[rfpath][txcnt] == 0xFF)
				pwrinfo5g->ofdm_diff[rfpath][txcnt] =	0xFE;
			else if (pwrinfo5g->ofdm_diff[rfpath][txcnt] & BIT(3))
				pwrinfo5g->ofdm_diff[rfpath][txcnt] |= 0xF0;
		}
	}
}