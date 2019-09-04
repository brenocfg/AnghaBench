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
typedef  scalar_t__ uint8_t ;
struct sk_buff {int dummy; } ;
struct net_device {int flags; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_2__ {scalar_t__ dest; int /*<<< orphan*/  source; } ;
struct archdr {TYPE_1__ hard; } ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 struct archdr* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int build_header(struct sk_buff *skb, struct net_device *dev,
			unsigned short type, uint8_t daddr)
{
	int hdr_size = ARC_HDR_SIZE;
	struct archdr *pkt = skb_push(skb, hdr_size);

	/* Set the source hardware address.
	 *
	 * This is pretty pointless for most purposes, but it can help in
	 * debugging.  ARCnet does not allow us to change the source address
	 * in the actual packet sent.
	 */
	pkt->hard.source = *dev->dev_addr;

	/* see linux/net/ethernet/eth.c to see where I got the following */

	if (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) {
		/* FIXME: fill in the last byte of the dest ipaddr here
		 * to better comply with RFC1051 in "noarp" mode.
		 */
		pkt->hard.dest = 0;
		return hdr_size;
	}
	/* otherwise, just fill it in and go! */
	pkt->hard.dest = daddr;

	return hdr_size;	/* success */
}