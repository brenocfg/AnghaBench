#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ duration_id; int /*<<< orphan*/  frame_ctl; } ;
struct rtllib_probe_request {TYPE_2__ header; } ;
struct TYPE_6__ {unsigned int ssid_len; int /*<<< orphan*/  ssid; } ;
struct rtllib_device {TYPE_3__ current_network; TYPE_1__* dev; scalar_t__ tx_headroom; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFIE_TYPE_SSID ; 
 int /*<<< orphan*/  RTLLIB_STYPE_PROBE_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rtllib_MFIE_Brate (struct rtllib_device*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  rtllib_MFIE_Grate (struct rtllib_device*,int /*<<< orphan*/ **) ; 
 unsigned int rtllib_MFIE_rate_len (struct rtllib_device*) ; 
 void* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static inline struct sk_buff *rtllib_probe_req(struct rtllib_device *ieee)
{
	unsigned int len, rate_len;
	u8 *tag;
	struct sk_buff *skb;
	struct rtllib_probe_request *req;

	len = ieee->current_network.ssid_len;

	rate_len = rtllib_MFIE_rate_len(ieee);

	skb = dev_alloc_skb(sizeof(struct rtllib_probe_request) +
			    2 + len + rate_len + ieee->tx_headroom);

	if (!skb)
		return NULL;

	skb_reserve(skb, ieee->tx_headroom);

	req = skb_put(skb, sizeof(struct rtllib_probe_request));
	req->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_PROBE_REQ);
	req->header.duration_id = 0;

	eth_broadcast_addr(req->header.addr1);
	ether_addr_copy(req->header.addr2, ieee->dev->dev_addr);
	eth_broadcast_addr(req->header.addr3);

	tag = skb_put(skb, len + 2 + rate_len);

	*tag++ = MFIE_TYPE_SSID;
	*tag++ = len;
	memcpy(tag, ieee->current_network.ssid, len);
	tag += len;

	rtllib_MFIE_Brate(ieee, &tag);
	rtllib_MFIE_Grate(ieee, &tag);

	return skb;
}