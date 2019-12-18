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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ ETH_P_PAE ; 
 scalar_t__ be16_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 int /*<<< orphan*/ * rtl_skb_ether_type_ptr (struct ieee80211_hw*,struct sk_buff*,int) ; 

bool rtl_is_tx_report_skb(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	u16 ether_type;
	const u8 *ether_type_ptr;
	__le16 fc = rtl_get_fc(skb);

	ether_type_ptr = rtl_skb_ether_type_ptr(hw, skb, true);
	ether_type = be16_to_cpup((__be16 *)ether_type_ptr);

	if (ether_type == ETH_P_PAE || ieee80211_is_nullfunc(fc))
		return true;

	return false;
}