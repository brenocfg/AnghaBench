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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  AC0_BE 131 
#define  AC1_BK 130 
#define  AC2_VI 129 
#define  AC3_VO 128 
 int /*<<< orphan*/  REG_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  rtl92c_dm_init_edca_turbo (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92ce_set_qos(struct ieee80211_hw *hw, int aci)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl92c_dm_init_edca_turbo(hw);
	switch (aci) {
	case AC1_BK:
		rtl_write_dword(rtlpriv, REG_EDCA_BK_PARAM, 0xa44f);
		break;
	case AC0_BE:
		/* rtl_write_dword(rtlpriv, REG_EDCA_BE_PARAM, u4b_ac_param); */
		break;
	case AC2_VI:
		rtl_write_dword(rtlpriv, REG_EDCA_VI_PARAM, 0x5e4322);
		break;
	case AC3_VO:
		rtl_write_dword(rtlpriv, REG_EDCA_VO_PARAM, 0x2f3222);
		break;
	default:
		WARN_ONCE(true, "rtl8192ce: invalid aci: %d !\n", aci);
		break;
	}
}