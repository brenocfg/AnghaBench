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
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
struct rtl_priv {TYPE_2__ mac80211; } ;
struct TYPE_3__ {int bt_lps_on; scalar_t__ bt_ctrl_lps; } ;
struct btc_coexist {TYPE_1__ bt_info; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_lps_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtc_pre_normal_lps(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->bt_info.bt_ctrl_lps) {
		btcoexist->bt_info.bt_lps_on = false;
		rtl_lps_leave(rtlpriv->mac80211.hw);
	}
}