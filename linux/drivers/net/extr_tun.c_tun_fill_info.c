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
struct tun_struct {int flags; int /*<<< orphan*/  numdisabled; int /*<<< orphan*/  numqueues; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int IFF_MULTI_QUEUE ; 
 int IFF_NO_PI ; 
 int IFF_PERSIST ; 
 int IFF_VNET_HDR ; 
 int /*<<< orphan*/  IFLA_TUN_GROUP ; 
 int /*<<< orphan*/  IFLA_TUN_MULTI_QUEUE ; 
 int /*<<< orphan*/  IFLA_TUN_NUM_DISABLED_QUEUES ; 
 int /*<<< orphan*/  IFLA_TUN_NUM_QUEUES ; 
 int /*<<< orphan*/  IFLA_TUN_OWNER ; 
 int /*<<< orphan*/  IFLA_TUN_PERSIST ; 
 int /*<<< orphan*/  IFLA_TUN_PI ; 
 int /*<<< orphan*/  IFLA_TUN_TYPE ; 
 int /*<<< orphan*/  IFLA_TUN_VNET_HDR ; 
 int TUN_TYPE_MASK ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gid_valid (int /*<<< orphan*/ ) ; 
 struct tun_struct* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tun_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	if (nla_put_u8(skb, IFLA_TUN_TYPE, tun->flags & TUN_TYPE_MASK))
		goto nla_put_failure;
	if (uid_valid(tun->owner) &&
	    nla_put_u32(skb, IFLA_TUN_OWNER,
			from_kuid_munged(current_user_ns(), tun->owner)))
		goto nla_put_failure;
	if (gid_valid(tun->group) &&
	    nla_put_u32(skb, IFLA_TUN_GROUP,
			from_kgid_munged(current_user_ns(), tun->group)))
		goto nla_put_failure;
	if (nla_put_u8(skb, IFLA_TUN_PI, !(tun->flags & IFF_NO_PI)))
		goto nla_put_failure;
	if (nla_put_u8(skb, IFLA_TUN_VNET_HDR, !!(tun->flags & IFF_VNET_HDR)))
		goto nla_put_failure;
	if (nla_put_u8(skb, IFLA_TUN_PERSIST, !!(tun->flags & IFF_PERSIST)))
		goto nla_put_failure;
	if (nla_put_u8(skb, IFLA_TUN_MULTI_QUEUE,
		       !!(tun->flags & IFF_MULTI_QUEUE)))
		goto nla_put_failure;
	if (tun->flags & IFF_MULTI_QUEUE) {
		if (nla_put_u32(skb, IFLA_TUN_NUM_QUEUES, tun->numqueues))
			goto nla_put_failure;
		if (nla_put_u32(skb, IFLA_TUN_NUM_DISABLED_QUEUES,
				tun->numdisabled))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}