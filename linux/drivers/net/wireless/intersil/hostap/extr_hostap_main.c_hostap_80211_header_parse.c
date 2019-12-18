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

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 scalar_t__ skb_mac_header (struct sk_buff const*) ; 

__attribute__((used)) static int hostap_80211_header_parse(const struct sk_buff *skb,
				     unsigned char *haddr)
{
	memcpy(haddr, skb_mac_header(skb) + 10, ETH_ALEN); /* addr2 */
	return ETH_ALEN;
}