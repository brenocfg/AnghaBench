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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct rtllib_network {int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ duration_id; void* frame_ctl; } ;
struct rtllib_disauth {void* reason; TYPE_2__ header; } ;
struct rtllib_device {TYPE_1__* dev; int /*<<< orphan*/  tx_headroom; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTLLIB_STYPE_DEAUTH ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtllib_disauth* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *
rtllib_disauth_skb(struct rtllib_network *beacon,
		   struct rtllib_device *ieee, u16 asRsn)
{
	struct sk_buff *skb;
	struct rtllib_disauth *disauth;
	int len = sizeof(struct rtllib_disauth) + ieee->tx_headroom;

	skb = dev_alloc_skb(len);
	if (!skb)
		return NULL;

	skb_reserve(skb, ieee->tx_headroom);

	disauth = skb_put(skb, sizeof(struct rtllib_disauth));
	disauth->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_DEAUTH);
	disauth->header.duration_id = 0;

	ether_addr_copy(disauth->header.addr1, beacon->bssid);
	ether_addr_copy(disauth->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(disauth->header.addr3, beacon->bssid);

	disauth->reason = cpu_to_le16(asRsn);
	return skb;
}