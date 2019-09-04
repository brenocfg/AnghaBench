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
struct net_device {int flags; int hard_header_len; int /*<<< orphan*/  addr_len; } ;
struct fwnet_header {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be16 (unsigned short,int /*<<< orphan*/ *) ; 
 struct fwnet_header* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int fwnet_header_create(struct sk_buff *skb, struct net_device *net,
			unsigned short type, const void *daddr,
			const void *saddr, unsigned len)
{
	struct fwnet_header *h;

	h = skb_push(skb, sizeof(*h));
	put_unaligned_be16(type, &h->h_proto);

	if (net->flags & (IFF_LOOPBACK | IFF_NOARP)) {
		memset(h->h_dest, 0, net->addr_len);

		return net->hard_header_len;
	}

	if (daddr) {
		memcpy(h->h_dest, daddr, net->addr_len);

		return net->hard_header_len;
	}

	return -net->hard_header_len;
}