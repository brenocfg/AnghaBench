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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct rtllib_rx_stats {int /*<<< orphan*/  len; } ;
struct rtllib_hdr_3addr {int /*<<< orphan*/  addr1; } ;
struct rtllib_device {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_rx_frame_softmac (struct rtllib_device*,struct sk_buff*,struct rtllib_rx_stats*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_rx_mgt (struct rtllib_device*,struct sk_buff*,struct rtllib_rx_stats*) ; 

__attribute__((used)) static inline int
rtllib_rx_frame_mgmt(struct rtllib_device *ieee, struct sk_buff *skb,
			struct rtllib_rx_stats *rx_stats, u16 type,
			u16 stype)
{
	/* On the struct stats definition there is written that
	 * this is not mandatory.... but seems that the probe
	 * response parser uses it
	 */
	struct rtllib_hdr_3addr *hdr = (struct rtllib_hdr_3addr *)skb->data;

	rx_stats->len = skb->len;
	rtllib_rx_mgt(ieee, skb, rx_stats);
	if ((memcmp(hdr->addr1, ieee->dev->dev_addr, ETH_ALEN))) {
		dev_kfree_skb_any(skb);
		return 0;
	}
	rtllib_rx_frame_softmac(ieee, skb, rx_stats, type, stype);

	dev_kfree_skb_any(skb);

	return 0;
}