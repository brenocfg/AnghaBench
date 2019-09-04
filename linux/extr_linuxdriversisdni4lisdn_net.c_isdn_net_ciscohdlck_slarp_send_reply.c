#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_mask; int /*<<< orphan*/  ifa_local; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;
struct TYPE_9__ {TYPE_2__* netdev; } ;
typedef  TYPE_3__ isdn_net_local ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_8__ {TYPE_1__* dev; } ;
struct TYPE_7__ {struct in_device* ip_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISCO_ADDR_UNICAST ; 
 int /*<<< orphan*/  CISCO_CTRL ; 
 int /*<<< orphan*/  CISCO_SLARP_REPLY ; 
 int /*<<< orphan*/  CISCO_TYPE_SLARP ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* isdn_net_ciscohdlck_alloc_skb (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isdn_net_write_super (TYPE_3__*,struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
isdn_net_ciscohdlck_slarp_send_reply(isdn_net_local *lp)
{
	struct sk_buff *skb;
	unsigned char *p;
	struct in_device *in_dev = NULL;
	__be32 addr = 0;		/* local ipv4 address */
	__be32 mask = 0;		/* local netmask */

	if ((in_dev = lp->netdev->dev->ip_ptr) != NULL) {
		/* take primary(first) address of interface */
		struct in_ifaddr *ifa = in_dev->ifa_list;
		if (ifa != NULL) {
			addr = ifa->ifa_local;
			mask = ifa->ifa_mask;
		}
	}

	skb = isdn_net_ciscohdlck_alloc_skb(lp, 4 + 14);
	if (!skb)
		return;

	p = skb_put(skb, 4 + 14);

	/* cisco header */
	*(u8 *)(p + 0) = CISCO_ADDR_UNICAST;
	*(u8 *)(p + 1) = CISCO_CTRL;
	*(__be16 *)(p + 2) = cpu_to_be16(CISCO_TYPE_SLARP);

	/* slarp reply, send own ip/netmask; if values are nonsense remote
	 * should think we are unable to provide it with an address via SLARP */
	*(__be32 *)(p +  4) = cpu_to_be32(CISCO_SLARP_REPLY);
	*(__be32 *)(p +  8) = addr; // address
	*(__be32 *)(p + 12) = mask; // netmask
	*(__be16 *)(p + 16) = cpu_to_be16(0); // unused
	p += 18;

	isdn_net_write_super(lp, skb);
}