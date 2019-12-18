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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {TYPE_1__* intf_ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl_op_flush(struct ieee80211_hw *hw,
			 struct ieee80211_vif *vif,
			 u32 queues,
			 bool drop)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (rtlpriv->intf_ops->flush)
		rtlpriv->intf_ops->flush(hw, queues, drop);
}