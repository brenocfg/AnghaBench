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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iphdr {unsigned int protocol; int tot_len; int ihl; int saddr; int daddr; } ;
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_HLEN ; 
 int ETH_P_IP ; 
 unsigned int IPPROTO_TCP ; 
 unsigned int IPPROTO_UDP ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int htons (int) ; 
 scalar_t__ ip_is_fragment (struct iphdr*) ; 

__attribute__((used)) static void ioc3_tcpudp_checksum(struct sk_buff *skb, u32 hwsum, int len)
{
	struct ethhdr *eh = eth_hdr(skb);
	unsigned int proto;
	unsigned char *cp;
	struct iphdr *ih;
	u32 csum, ehsum;
	u16 *ew;

	/* Did hardware handle the checksum at all?  The cases we can handle
	 * are:
	 *
	 * - TCP and UDP checksums of IPv4 only.
	 * - IPv6 would be doable but we keep that for later ...
	 * - Only unfragmented packets.  Did somebody already tell you
	 *   fragmentation is evil?
	 * - don't care about packet size.  Worst case when processing a
	 *   malformed packet we'll try to access the packet at ip header +
	 *   64 bytes which is still inside the skb.  Even in the unlikely
	 *   case where the checksum is right the higher layers will still
	 *   drop the packet as appropriate.
	 */
	if (eh->h_proto != htons(ETH_P_IP))
		return;

	ih = (struct iphdr *)((char *)eh + ETH_HLEN);
	if (ip_is_fragment(ih))
		return;

	proto = ih->protocol;
	if (proto != IPPROTO_TCP && proto != IPPROTO_UDP)
		return;

	/* Same as tx - compute csum of pseudo header  */
	csum = hwsum +
	       (ih->tot_len - (ih->ihl << 2)) +
	       htons((u16)ih->protocol) +
	       (ih->saddr >> 16) + (ih->saddr & 0xffff) +
	       (ih->daddr >> 16) + (ih->daddr & 0xffff);

	/* Sum up ethernet dest addr, src addr and protocol  */
	ew = (u16 *)eh;
	ehsum = ew[0] + ew[1] + ew[2] + ew[3] + ew[4] + ew[5] + ew[6];

	ehsum = (ehsum & 0xffff) + (ehsum >> 16);
	ehsum = (ehsum & 0xffff) + (ehsum >> 16);

	csum += 0xffff ^ ehsum;

	/* In the next step we also subtract the 1's complement
	 * checksum of the trailing ethernet CRC.
	 */
	cp = (char *)eh + len;	/* points at trailing CRC */
	if (len & 1) {
		csum += 0xffff ^ (u16)((cp[1] << 8) | cp[0]);
		csum += 0xffff ^ (u16)((cp[3] << 8) | cp[2]);
	} else {
		csum += 0xffff ^ (u16)((cp[0] << 8) | cp[1]);
		csum += 0xffff ^ (u16)((cp[2] << 8) | cp[3]);
	}

	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);

	if (csum == 0xffff)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
}