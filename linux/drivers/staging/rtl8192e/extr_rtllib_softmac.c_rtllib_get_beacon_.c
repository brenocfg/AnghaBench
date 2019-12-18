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
typedef  int u8 ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_ctl; } ;
struct rtllib_probe_response {TYPE_1__ header; } ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTLLIB_STYPE_BEACON ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* rtllib_probe_resp (struct rtllib_device*,int const*) ; 

__attribute__((used)) static struct sk_buff *rtllib_get_beacon_(struct rtllib_device *ieee)
{
	static const u8 broadcast_addr[] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
	struct sk_buff *skb;
	struct rtllib_probe_response *b;

	skb = rtllib_probe_resp(ieee, broadcast_addr);

	if (!skb)
		return NULL;

	b = (struct rtllib_probe_response *) skb->data;
	b->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_BEACON);

	return skb;

}