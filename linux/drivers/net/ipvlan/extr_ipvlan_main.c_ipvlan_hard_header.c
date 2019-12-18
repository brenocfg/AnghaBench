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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ipvl_dev {struct net_device* phy_dev; } ;

/* Variables and functions */
 int dev_hard_header (struct sk_buff*,struct net_device*,unsigned short,void const*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipvlan_hard_header(struct sk_buff *skb, struct net_device *dev,
			      unsigned short type, const void *daddr,
			      const void *saddr, unsigned len)
{
	const struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct net_device *phy_dev = ipvlan->phy_dev;

	/* TODO Probably use a different field than dev_addr so that the
	 * mac-address on the virtual device is portable and can be carried
	 * while the packets use the mac-addr on the physical device.
	 */
	return dev_hard_header(skb, phy_dev, type, daddr,
			       saddr ? : phy_dev->dev_addr, len);
}