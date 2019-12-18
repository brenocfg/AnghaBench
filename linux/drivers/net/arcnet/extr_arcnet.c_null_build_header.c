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
typedef  size_t uint8_t ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct arcnet_local {int /*<<< orphan*/ * default_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROTO ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int null_build_header(struct sk_buff *skb, struct net_device *dev,
			     unsigned short type, uint8_t daddr)
{
	struct arcnet_local *lp = netdev_priv(dev);

	arc_printk(D_PROTO, dev,
		   "tx: can't build header for encap %02Xh; load a protocol driver.\n",
		   lp->default_proto[daddr]);

	/* always fails */
	return 0;
}