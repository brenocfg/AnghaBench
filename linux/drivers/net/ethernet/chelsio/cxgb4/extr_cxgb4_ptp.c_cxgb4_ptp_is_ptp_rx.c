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
struct udphdr {scalar_t__ dest; scalar_t__ source; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ IPV4_HLEN (scalar_t__) ; 
 int /*<<< orphan*/  PTP_EVENT_PORT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

bool cxgb4_ptp_is_ptp_rx(struct sk_buff *skb)
{
	struct udphdr *uh = (struct udphdr *)(skb->data + ETH_HLEN +
					      IPV4_HLEN(skb->data));

	return  uh->dest == htons(PTP_EVENT_PORT) &&
		uh->source == htons(PTP_EVENT_PORT);
}