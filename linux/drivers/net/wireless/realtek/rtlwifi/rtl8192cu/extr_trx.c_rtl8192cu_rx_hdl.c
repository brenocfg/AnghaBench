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
struct sk_buff {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl_rx_process (struct ieee80211_hw*,struct sk_buff*) ; 

void  rtl8192cu_rx_hdl(struct ieee80211_hw *hw, struct sk_buff * skb)
{
	_rtl_rx_process(hw, skb);
}