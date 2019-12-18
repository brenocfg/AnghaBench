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
struct dst_entry {int /*<<< orphan*/  dev; } ;
struct rtable {struct dst_entry dst; } ;
struct net_vrf {int /*<<< orphan*/  rth; } ;
struct net_device {int dummy; } ;
struct net {int /*<<< orphan*/  loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct rtable* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void vrf_rtable_release(struct net_device *dev, struct net_vrf *vrf)
{
	struct rtable *rth = rtnl_dereference(vrf->rth);
	struct net *net = dev_net(dev);
	struct dst_entry *dst;

	RCU_INIT_POINTER(vrf->rth, NULL);
	synchronize_rcu();

	/* move dev in dst's to loopback so this VRF device can be deleted
	 * - based on dst_ifdown
	 */
	if (rth) {
		dst = &rth->dst;
		dev_put(dst->dev);
		dst->dev = net->loopback_dev;
		dev_hold(dst->dev);
		dst_release(dst);
	}
}