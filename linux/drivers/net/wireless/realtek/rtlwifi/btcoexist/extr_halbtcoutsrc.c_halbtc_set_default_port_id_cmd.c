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
struct TYPE_4__ {struct ieee80211_hw* hw; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_default_port_id_cmd ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

void halbtc_set_default_port_id_cmd(void *bt_context)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)bt_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct ieee80211_hw *hw = rtlpriv->mac80211.hw;

	if (!rtlpriv->cfg->ops->set_default_port_id_cmd)
		return;

	rtlpriv->cfg->ops->set_default_port_id_cmd(hw);
}