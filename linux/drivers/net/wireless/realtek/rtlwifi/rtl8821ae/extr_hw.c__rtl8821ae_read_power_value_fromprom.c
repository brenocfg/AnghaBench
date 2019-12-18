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
struct txpower_info_5g {int** index_bw40_base; int** ofdm_diff; int** bw20_diff; int** bw80_diff; int** bw160_diff; int** bw40_diff; } ;
struct txpower_info_2g {int** index_cck_base; int** index_bw40_base; int** bw20_diff; int** ofdm_diff; int** bw40_diff; int** cck_diff; } ;
struct TYPE_2__ {int txpwr_fromeprom; } ;
struct rtl_priv {TYPE_1__ efuse; } ;
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

__attribute__((used)) static void _rtl8821ae_read_power_value_fromprom(struct ieee80211_hw *hw,
	struct txpower_info_2g *pwrinfo24g,
	struct txpower_info_5g *pwrinfo5g,
	bool autoload_fail,
	u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 rfpath, eeaddr = EEPROM_TX_PWR_INX, group, txcount = 0;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "hal_ReadPowerValueFromPROM8821ae(): hwinfo[0x%x]=0x%x\n",
		 (eeaddr + 1), hwinfo[eeaddr + 1]);
	if (hwinfo[eeaddr + 1] == 0xFF)  /*YJ,add,120316*/
		autoload_fail = true;

	if (autoload_fail) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "auto load fail : Use Default value!\n");
		for (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) {
			/*2.4G default value*/
			for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
				pwrinfo24g->index_cck_base[rfpath][group] = 0x2D;
				pwrinfo24g->index_bw40_base[rfpath][group] = 0x2D;
			}
			for (txcount = 0; txcount < MAX_TX_COUNT; txcount++) {
				if (txcount == 0) {
					pwrinfo24g->bw20_diff[rfpath][0] = 0x02;
					pwrinfo24g->ofdm_diff[rfpath][0] = 0x04;
				} else {
					pwrinfo24g->bw20_diff[rfpath][txcount] = 0xFE;
					pwrinfo24g->bw40_diff[rfpath][txcount] = 0xFE;
					pwrinfo24g->cck_diff[rfpath][txcount] =	0xFE;
					pwrinfo24g->ofdm_diff[rfpath][txcount] = 0xFE;
				}
			}
			/*5G default value*/
			for (group = 0 ; group < MAX_CHNL_GROUP_5G; group++)
				pwrinfo5g->index_bw40_base[rfpath][group] = 0x2A;

			for (txcount = 0; txcount < MAX_TX_COUNT; txcount++) {
				if (txcount == 0) {
					pwrinfo5g->ofdm_diff[rfpath][0] = 0x04;
					pwrinfo5g->bw20_diff[rfpath][0] = 0x00;
					pwrinfo5g->bw80_diff[rfpath][0] = 0xFE;
					pwrinfo5g->bw160_diff[rfpath][0] = 0xFE;
				} else {
					pwrinfo5g->ofdm_diff[rfpath][0] = 0xFE;
					pwrinfo5g->bw20_diff[rfpath][0] = 0xFE;
					pwrinfo5g->bw40_diff[rfpath][0] = 0xFE;
					pwrinfo5g->bw80_diff[rfpath][0] = 0xFE;
					pwrinfo5g->bw160_diff[rfpath][0] = 0xFE;
				}
			}
		}
		return;
	}

	rtl_priv(hw)->efuse.txpwr_fromeprom = true;

	for (rfpath = 0 ; rfpath < MAX_RF_PATH ; rfpath++) {
		/*2.4G default value*/
		for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
			pwrinfo24g->index_cck_base[rfpath][group] = hwinfo[eeaddr++];
			if (pwrinfo24g->index_cck_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_cck_base[rfpath][group] = 0x2D;
		}
		for (group = 0 ; group < MAX_CHNL_GROUP_24G - 1; group++) {
			pwrinfo24g->index_bw40_base[rfpath][group] = hwinfo[eeaddr++];
			if (pwrinfo24g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo24g->index_bw40_base[rfpath][group] = 0x2D;
		}
		for (txcount = 0; txcount < MAX_TX_COUNT; txcount++) {
			if (txcount == 0) {
				pwrinfo24g->bw40_diff[rfpath][txcount] = 0;
				/*bit sign number to 8 bit sign number*/
				pwrinfo24g->bw20_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				if (pwrinfo24g->bw20_diff[rfpath][txcount] & BIT(3))
					pwrinfo24g->bw20_diff[rfpath][txcount] |= 0xF0;
				/*bit sign number to 8 bit sign number*/
				pwrinfo24g->ofdm_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
				if (pwrinfo24g->ofdm_diff[rfpath][txcount] & BIT(3))
					pwrinfo24g->ofdm_diff[rfpath][txcount] |= 0xF0;

				pwrinfo24g->cck_diff[rfpath][txcount] = 0;
				eeaddr++;
			} else {
				pwrinfo24g->bw40_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				if (pwrinfo24g->bw40_diff[rfpath][txcount] & BIT(3))
					pwrinfo24g->bw40_diff[rfpath][txcount] |= 0xF0;

				pwrinfo24g->bw20_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
				if (pwrinfo24g->bw20_diff[rfpath][txcount] & BIT(3))
					pwrinfo24g->bw20_diff[rfpath][txcount] |= 0xF0;

				eeaddr++;

				pwrinfo24g->ofdm_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				if (pwrinfo24g->ofdm_diff[rfpath][txcount] & BIT(3))
					pwrinfo24g->ofdm_diff[rfpath][txcount] |= 0xF0;

				pwrinfo24g->cck_diff[rfpath][txcount] =	(hwinfo[eeaddr] & 0x0f);
				if (pwrinfo24g->cck_diff[rfpath][txcount] & BIT(3))
					pwrinfo24g->cck_diff[rfpath][txcount] |= 0xF0;

				eeaddr++;
			}
		}

		/*5G default value*/
		for (group = 0 ; group < MAX_CHNL_GROUP_5G; group++) {
			pwrinfo5g->index_bw40_base[rfpath][group] = hwinfo[eeaddr++];
			if (pwrinfo5g->index_bw40_base[rfpath][group] == 0xFF)
				pwrinfo5g->index_bw40_base[rfpath][group] = 0xFE;
		}

		for (txcount = 0; txcount < MAX_TX_COUNT; txcount++) {
			if (txcount == 0) {
				pwrinfo5g->bw40_diff[rfpath][txcount] = 0;

				pwrinfo5g->bw20_diff[rfpath][0] = (hwinfo[eeaddr] & 0xf0) >> 4;
				if (pwrinfo5g->bw20_diff[rfpath][txcount] & BIT(3))
					pwrinfo5g->bw20_diff[rfpath][txcount] |= 0xF0;

				pwrinfo5g->ofdm_diff[rfpath][0] = (hwinfo[eeaddr] & 0x0f);
				if (pwrinfo5g->ofdm_diff[rfpath][txcount] & BIT(3))
					pwrinfo5g->ofdm_diff[rfpath][txcount] |= 0xF0;

				eeaddr++;
			} else {
				pwrinfo5g->bw40_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0xf0) >> 4;
				if (pwrinfo5g->bw40_diff[rfpath][txcount] & BIT(3))
					pwrinfo5g->bw40_diff[rfpath][txcount] |= 0xF0;

				pwrinfo5g->bw20_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
				if (pwrinfo5g->bw20_diff[rfpath][txcount] & BIT(3))
					pwrinfo5g->bw20_diff[rfpath][txcount] |= 0xF0;

				eeaddr++;
			}
		}

		pwrinfo5g->ofdm_diff[rfpath][1] =	(hwinfo[eeaddr] & 0xf0) >> 4;
		pwrinfo5g->ofdm_diff[rfpath][2] =	(hwinfo[eeaddr] & 0x0f);

		eeaddr++;

		pwrinfo5g->ofdm_diff[rfpath][3] = (hwinfo[eeaddr] & 0x0f);

		eeaddr++;

		for (txcount = 1; txcount < MAX_TX_COUNT; txcount++) {
			if (pwrinfo5g->ofdm_diff[rfpath][txcount] & BIT(3))
				pwrinfo5g->ofdm_diff[rfpath][txcount] |= 0xF0;
		}
		for (txcount = 0; txcount < MAX_TX_COUNT; txcount++) {
			pwrinfo5g->bw80_diff[rfpath][txcount] =	(hwinfo[eeaddr] & 0xf0) >> 4;
			/* 4bit sign number to 8 bit sign number */
			if (pwrinfo5g->bw80_diff[rfpath][txcount] & BIT(3))
				pwrinfo5g->bw80_diff[rfpath][txcount] |= 0xF0;
			/* 4bit sign number to 8 bit sign number */
			pwrinfo5g->bw160_diff[rfpath][txcount] = (hwinfo[eeaddr] & 0x0f);
			if (pwrinfo5g->bw160_diff[rfpath][txcount] & BIT(3))
				pwrinfo5g->bw160_diff[rfpath][txcount] |= 0xF0;

			eeaddr++;
		}
	}
}