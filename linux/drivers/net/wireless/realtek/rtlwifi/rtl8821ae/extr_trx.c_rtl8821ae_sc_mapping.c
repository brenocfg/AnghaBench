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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_tcb_desc {scalar_t__ packet_bw; } ;
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ cur_80_prime_sc; scalar_t__ cur_40_prime_sc; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_LOWER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_LOWEST_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_UPPERST_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_UPPER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_40_LOWER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_40_UPPER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_DONOT_CARE ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 rtl8821ae_sc_mapping(struct ieee80211_hw *hw,
			       struct rtl_tcb_desc *ptcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	u8 sc_setting_of_desc = 0;

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) {
		if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_80) {
			sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
		} else if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) {
			if (mac->cur_80_prime_sc ==
			    HAL_PRIME_CHNL_OFFSET_LOWER)
				sc_setting_of_desc =
					VHT_DATA_SC_40_LOWER_OF_80MHZ;
			else if (mac->cur_80_prime_sc ==
				 HAL_PRIME_CHNL_OFFSET_UPPER)
				sc_setting_of_desc =
					VHT_DATA_SC_40_UPPER_OF_80MHZ;
			else
				RT_TRACE(rtlpriv, COMP_SEND, DBG_LOUD,
					 "rtl8821ae_sc_mapping: Not Correct Primary40MHz Setting\n");
		} else {
			if ((mac->cur_40_prime_sc ==
			     HAL_PRIME_CHNL_OFFSET_LOWER) &&
			    (mac->cur_80_prime_sc  ==
			     HAL_PRIME_CHNL_OFFSET_LOWER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_LOWEST_OF_80MHZ;
			else if ((mac->cur_40_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER) &&
				 (mac->cur_80_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_LOWER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_LOWER_OF_80MHZ;
			else if ((mac->cur_40_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_LOWER) &&
				 (mac->cur_80_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_UPPER_OF_80MHZ;
			else if ((mac->cur_40_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER) &&
				 (mac->cur_80_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_UPPERST_OF_80MHZ;
			else
				RT_TRACE(rtlpriv, COMP_SEND, DBG_LOUD,
					 "rtl8821ae_sc_mapping: Not Correct Primary40MHz Setting\n");
		}
	} else if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
		if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) {
			sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
		} else if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20) {
			if (mac->cur_40_prime_sc ==
				HAL_PRIME_CHNL_OFFSET_UPPER) {
				sc_setting_of_desc =
					VHT_DATA_SC_20_UPPER_OF_80MHZ;
			} else if (mac->cur_40_prime_sc ==
				HAL_PRIME_CHNL_OFFSET_LOWER){
				sc_setting_of_desc =
					VHT_DATA_SC_20_LOWER_OF_80MHZ;
			} else {
				sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
			}
		}
	} else {
		sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
	}

	return sc_setting_of_desc;
}