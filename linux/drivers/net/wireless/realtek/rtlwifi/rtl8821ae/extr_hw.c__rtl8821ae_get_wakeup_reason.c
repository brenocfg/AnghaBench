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
struct rtl_ps_ctl {scalar_t__ wakeup_reason; } ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int /*<<< orphan*/  last_suspend_sec; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  FW_WOW_V2_DEAUTH_EVENT 138 
#define  FW_WOW_V2_DISASSOC_EVENT 137 
#define  FW_WOW_V2_FW_DISCONNECT_EVENT 136 
#define  FW_WOW_V2_GTK_UPDATE_EVENT 135 
#define  FW_WOW_V2_MAGIC_PKT_EVENT 134 
#define  FW_WOW_V2_PATTERN_PKT_EVENT 133 
#define  FW_WOW_V2_PTK_UPDATE_EVENT 132 
#define  FW_WOW_V2_REALWOW_V2_ACKLOST 131 
#define  FW_WOW_V2_REALWOW_V2_WAKEUPPKT 130 
#define  FW_WOW_V2_RTD3_SSID_MATCH_EVENT 129 
#define  FW_WOW_V2_UNICAST_PKT_EVENT 128 
 int /*<<< orphan*/  REG_MCUTST_WOWLAN ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ WOL_REASON_AP_LOST ; 
 scalar_t__ WOL_REASON_DEAUTH ; 
 scalar_t__ WOL_REASON_DISASSOC ; 
 scalar_t__ WOL_REASON_GTK_UPDATE ; 
 scalar_t__ WOL_REASON_MAGIC_PKT ; 
 scalar_t__ WOL_REASON_PATTERN_PKT ; 
 scalar_t__ WOL_REASON_PTK_UPDATE ; 
 scalar_t__ WOL_REASON_REALWOW_V2_ACKLOST ; 
 scalar_t__ WOL_REASON_REALWOW_V2_WAKEUPPKT ; 
 scalar_t__ WOL_REASON_RTD3_SSID_MATCH ; 
 scalar_t__ WOL_REASON_UNICAST_PKT ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl8821ae_get_wakeup_reason(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	u8 fw_reason = 0;

	fw_reason = rtl_read_byte(rtlpriv, REG_MCUTST_WOWLAN);

	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "WOL Read 0x1c7 = %02X\n",
		 fw_reason);

	ppsc->wakeup_reason = 0;

	rtlhal->last_suspend_sec = ktime_get_real_seconds();

	switch (fw_reason) {
	case FW_WOW_V2_PTK_UPDATE_EVENT:
		ppsc->wakeup_reason = WOL_REASON_PTK_UPDATE;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a WOL PTK Key update event!\n");
		break;
	case FW_WOW_V2_GTK_UPDATE_EVENT:
		ppsc->wakeup_reason = WOL_REASON_GTK_UPDATE;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a WOL GTK Key update event!\n");
		break;
	case FW_WOW_V2_DISASSOC_EVENT:
		ppsc->wakeup_reason = WOL_REASON_DISASSOC;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a disassociation event!\n");
		break;
	case FW_WOW_V2_DEAUTH_EVENT:
		ppsc->wakeup_reason = WOL_REASON_DEAUTH;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a deauth event!\n");
		break;
	case FW_WOW_V2_FW_DISCONNECT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_AP_LOST;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a Fw disconnect decision (AP lost) event!\n");
	break;
	case FW_WOW_V2_MAGIC_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_MAGIC_PKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a magic packet event!\n");
		break;
	case FW_WOW_V2_UNICAST_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_UNICAST_PKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an unicast packet event!\n");
		break;
	case FW_WOW_V2_PATTERN_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_PATTERN_PKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a pattern match event!\n");
		break;
	case FW_WOW_V2_RTD3_SSID_MATCH_EVENT:
		ppsc->wakeup_reason = WOL_REASON_RTD3_SSID_MATCH;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an RTD3 Ssid match event!\n");
		break;
	case FW_WOW_V2_REALWOW_V2_WAKEUPPKT:
		ppsc->wakeup_reason = WOL_REASON_REALWOW_V2_WAKEUPPKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an RealWoW wake packet event!\n");
		break;
	case FW_WOW_V2_REALWOW_V2_ACKLOST:
		ppsc->wakeup_reason = WOL_REASON_REALWOW_V2_ACKLOST;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an RealWoW ack lost event!\n");
		break;
	default:
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "WOL Read 0x1c7 = %02X, Unknown reason!\n",
			  fw_reason);
		break;
	}
}