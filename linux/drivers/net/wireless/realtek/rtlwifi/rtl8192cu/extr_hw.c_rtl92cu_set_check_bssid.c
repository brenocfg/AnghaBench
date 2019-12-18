#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ rfpwr_state; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ psc; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  HW_VAR_RCR ; 
 scalar_t__ IS_NORMAL_CHIP (int /*<<< orphan*/ ) ; 
 int RCR_CBSSID ; 
 int RCR_CBSSID_BCN ; 
 int RCR_CBSSID_DATA ; 
 int /*<<< orphan*/  _rtl92cu_set_bcn_ctrl_reg (struct ieee80211_hw*,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 

void rtl92cu_set_check_bssid(struct ieee80211_hw *hw, bool check_bssid)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 reg_rcr;

	if (rtlpriv->psc.rfpwr_state != ERFON)
		return;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));

	if (check_bssid) {
		u8 tmp;

		if (IS_NORMAL_CHIP(rtlhal->version)) {
			reg_rcr |= (RCR_CBSSID_DATA | RCR_CBSSID_BCN);
			tmp = BIT(4);
		} else {
			reg_rcr |= RCR_CBSSID;
			tmp = BIT(4) | BIT(5);
		}
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *) (&reg_rcr));
		_rtl92cu_set_bcn_ctrl_reg(hw, 0, tmp);
	} else {
		u8 tmp;

		if (IS_NORMAL_CHIP(rtlhal->version)) {
			reg_rcr &= ~(RCR_CBSSID_DATA | RCR_CBSSID_BCN);
			tmp = BIT(4);
		} else {
			reg_rcr &= ~RCR_CBSSID;
			tmp = BIT(4) | BIT(5);
		}
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		rtlpriv->cfg->ops->set_hw_reg(hw,
					      HW_VAR_RCR, (u8 *) (&reg_rcr));
		_rtl92cu_set_bcn_ctrl_reg(hw, tmp, 0);
	}
}