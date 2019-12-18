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
struct sk_buff {int dummy; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_ba_check (struct ar9170*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  carl9170_ps_beacon (struct ar9170*,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* carl9170_rx_copy_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_rx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 

__attribute__((used)) static int carl9170_handle_mpdu(struct ar9170 *ar, u8 *buf, int len,
				struct ieee80211_rx_status *status)
{
	struct sk_buff *skb;

	/* (driver) frame trap handler
	 *
	 * Because power-saving mode handing has to be implemented by
	 * the driver/firmware. We have to check each incoming beacon
	 * from the associated AP, if there's new data for us (either
	 * broadcast/multicast or unicast) we have to react quickly.
	 *
	 * So, if you have you want to add additional frame trap
	 * handlers, this would be the perfect place!
	 */

	carl9170_ps_beacon(ar, buf, len);

	carl9170_ba_check(ar, buf, len);

	skb = carl9170_rx_copy_data(buf, len);
	if (!skb)
		return -ENOMEM;

	memcpy(IEEE80211_SKB_RXCB(skb), status, sizeof(*status));
	ieee80211_rx(ar->hw, skb);
	return 0;
}