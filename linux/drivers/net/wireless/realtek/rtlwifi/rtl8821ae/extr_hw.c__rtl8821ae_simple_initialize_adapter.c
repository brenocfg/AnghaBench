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
struct rtl_ps_ctl {int /*<<< orphan*/  rfpwr_state; } ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int re_init_llt_table; scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERFON ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ _rtl8821ae_dynamic_rqpn (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_related_for_wowlan (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

__attribute__((used)) static void _rtl8821ae_simple_initialize_adapter(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);

#if (USE_SPECIFIC_FW_TO_SUPPORT_WOWLAN == 1)
	/* Re-download normal Fw. */
	rtl8821ae_set_fw_related_for_wowlan(hw, false);
#endif

	/* Re-Initialize LLT table. */
	if (rtlhal->re_init_llt_table) {
		u32 rqpn = 0x80e70808;
		u8 rqpn_npq = 0, boundary = 0xF8;
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			rqpn = 0x80e90808;
			boundary = 0xFA;
		}
		if (_rtl8821ae_dynamic_rqpn(hw, boundary, rqpn_npq, rqpn))
			rtlhal->re_init_llt_table = false;
	}

	ppsc->rfpwr_state = ERFON;
}