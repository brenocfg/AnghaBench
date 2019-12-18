#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_CTRL_FILTER ; 
 int /*<<< orphan*/  HW_VAR_DATA_FILTER ; 
 int /*<<< orphan*/  HW_VAR_MGT_FILTER ; 
 int /*<<< orphan*/  HW_VAR_RCR ; 
 int RCR_AB ; 
 int RCR_ACRC32 ; 
 int RCR_ADF ; 
 int RCR_AM ; 
 int RCR_AMF ; 
 int RCR_APM ; 
 int RCR_APPFCS ; 
 int RCR_APP_ICV ; 
 int RCR_APP_MIC ; 
 int RCR_APP_PHYSTS ; 
 int RCR_HTC_LOC_CTRL ; 
 scalar_t__ REG_MAR ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92cu_init_wmac_setting(struct ieee80211_hw *hw)
{
	u16 value16;
	u32 value32;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	value32 = (RCR_APM | RCR_AM | RCR_ADF | RCR_AB | RCR_APPFCS |
		   RCR_APP_ICV | RCR_AMF | RCR_HTC_LOC_CTRL |
		   RCR_APP_MIC | RCR_APP_PHYSTS | RCR_ACRC32);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR, (u8 *)(&value32));
	/* Accept all multicast address */
	rtl_write_dword(rtlpriv,  REG_MAR, 0xFFFFFFFF);
	rtl_write_dword(rtlpriv,  REG_MAR + 4, 0xFFFFFFFF);
	/* Accept all management frames */
	value16 = 0xFFFF;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_MGT_FILTER,
				      (u8 *)(&value16));
	/* Reject all control frame - default value is 0 */
	value16 = 0x0;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_CTRL_FILTER,
				      (u8 *)(&value16));
	/* Accept all data frames */
	value16 = 0xFFFF;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_DATA_FILTER,
				      (u8 *)(&value16));
}