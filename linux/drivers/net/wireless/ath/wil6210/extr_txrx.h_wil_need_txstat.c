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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ sk; } ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int SKBTX_WIFI_STATUS ; 
 scalar_t__ is_unicast_ether_addr (int /*<<< orphan*/  const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/ * wil_skb_get_da (struct sk_buff*) ; 

__attribute__((used)) static inline bool wil_need_txstat(struct sk_buff *skb)
{
	const u8 *da = wil_skb_get_da(skb);

	return is_unicast_ether_addr(da) && skb->sk &&
	       (skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS);
}