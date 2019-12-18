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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct TYPE_2__ {int CSM; } ;
struct rx_desc {TYPE_1__ rdesc1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int CSM_IPKT ; 
 int CSM_IPOK ; 
 int CSM_TCPKT ; 
 int CSM_TUPOK ; 
 int CSM_UDPKT ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void velocity_rx_csum(struct rx_desc *rd, struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);

	if (rd->rdesc1.CSM & CSM_IPKT) {
		if (rd->rdesc1.CSM & CSM_IPOK) {
			if ((rd->rdesc1.CSM & CSM_TCPKT) ||
					(rd->rdesc1.CSM & CSM_UDPKT)) {
				if (!(rd->rdesc1.CSM & CSM_TUPOK))
					return;
			}
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		}
	}
}