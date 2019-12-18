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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ bt_edca_dl; scalar_t__ bt_edca_ul; int /*<<< orphan*/  bt_rfreg_origin_1e; scalar_t__ bt_ant_isolation; scalar_t__ bt_cur_state; scalar_t__ bt_coexistence; } ;
struct rtl_priv {TYPE_3__ btcoexist; TYPE_2__* cfg; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_rfreg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IS_81XXC_VENDOR_UMC_B_CUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  rtl92c_bt_ant_isolation (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl92c_check_bt_change(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp1byte = 0;

	if (IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version) &&
	    rtlpriv->btcoexist.bt_coexistence)
		tmp1byte |= BIT(5);
	if (rtlpriv->btcoexist.bt_cur_state) {
		if (rtlpriv->btcoexist.bt_ant_isolation)
			rtl92c_bt_ant_isolation(hw, tmp1byte);
	} else {
		rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, tmp1byte);
		rtlpriv->cfg->ops->set_rfreg(hw, RF90_PATH_A, 0x1e, 0xf0,
				rtlpriv->btcoexist.bt_rfreg_origin_1e);

		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
	}
}