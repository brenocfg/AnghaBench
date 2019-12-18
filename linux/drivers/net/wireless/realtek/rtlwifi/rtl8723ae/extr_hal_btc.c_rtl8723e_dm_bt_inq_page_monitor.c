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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  cstate; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {scalar_t__ bt_inq_page_start_time; scalar_t__ c2h_bt_inquiry_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_COEX_STATE_BT_INQ_PAGE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 long HZ ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ hal_coex_8723 ; 
 scalar_t__ jiffies ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_inq_page_monitor(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cur_time;

	cur_time = jiffies;
	if (hal_coex_8723.c2h_bt_inquiry_page) {
		/* bt inquiry or page is started. */
		if (hal_coex_8723.bt_inq_page_start_time == 0) {
			rtlpriv->btcoexist.cstate  |=
			BT_COEX_STATE_BT_INQ_PAGE;
			hal_coex_8723.bt_inq_page_start_time = cur_time;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				 "[BTCoex], BT Inquiry/page is started at time : 0x%x\n",
				 hal_coex_8723.bt_inq_page_start_time);
		}
	}
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		 "[BTCoex], BT Inquiry/page started time : 0x%x, cur_time : 0x%x\n",
		 hal_coex_8723.bt_inq_page_start_time, cur_time);

	if (hal_coex_8723.bt_inq_page_start_time) {
		if ((((long)cur_time -
			(long)hal_coex_8723.bt_inq_page_start_time) / HZ)
			>= 10) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT Inquiry/page >= 10sec!!!\n");
			hal_coex_8723.bt_inq_page_start_time = 0;
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_BT_INQ_PAGE;
		}
	}
}