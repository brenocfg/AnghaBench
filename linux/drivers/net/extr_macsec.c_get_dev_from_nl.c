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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  netif_is_macsec (struct net_device*) ; 
 int nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static struct net_device *get_dev_from_nl(struct net *net,
					  struct nlattr **attrs)
{
	int ifindex = nla_get_u32(attrs[MACSEC_ATTR_IFINDEX]);
	struct net_device *dev;

	dev = __dev_get_by_index(net, ifindex);
	if (!dev)
		return ERR_PTR(-ENODEV);

	if (!netif_is_macsec(dev))
		return ERR_PTR(-ENODEV);

	return dev;
}