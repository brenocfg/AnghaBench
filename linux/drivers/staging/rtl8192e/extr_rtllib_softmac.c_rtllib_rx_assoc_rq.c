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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ass_rq; } ;
struct rtllib_device {int /*<<< orphan*/  dev; TYPE_1__ softmac_stats; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int assoc_rq_parse (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_resp_to_assoc_rq (struct rtllib_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rtllib_rx_assoc_rq(struct rtllib_device *ieee,
				      struct sk_buff *skb)
{
	u8 dest[ETH_ALEN];


	ieee->softmac_stats.rx_ass_rq++;
	if (assoc_rq_parse(ieee->dev, skb, dest) != -1)
		rtllib_resp_to_assoc_rq(ieee, dest);

	netdev_info(ieee->dev, "New client associated: %pM\n", dest);
}