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
struct net_device {int dummy; } ;
struct gtp_dev {int /*<<< orphan*/  hash_size; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_GTP_PDP_HASHSIZE ; 
 struct gtp_dev* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gtp_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct gtp_dev *gtp = netdev_priv(dev);

	if (nla_put_u32(skb, IFLA_GTP_PDP_HASHSIZE, gtp->hash_size))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}