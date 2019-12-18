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
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;
struct macsec_dev {struct net_device* real_dev; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int dev_uc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static int macsec_dev_open(struct net_device *dev)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	struct net_device *real_dev = macsec->real_dev;
	int err;

	err = dev_uc_add(real_dev, dev->dev_addr);
	if (err < 0)
		return err;

	if (dev->flags & IFF_ALLMULTI) {
		err = dev_set_allmulti(real_dev, 1);
		if (err < 0)
			goto del_unicast;
	}

	if (dev->flags & IFF_PROMISC) {
		err = dev_set_promiscuity(real_dev, 1);
		if (err < 0)
			goto clear_allmulti;
	}

	if (netif_carrier_ok(real_dev))
		netif_carrier_on(dev);

	return 0;
clear_allmulti:
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);
del_unicast:
	dev_uc_del(real_dev, dev->dev_addr);
	netif_carrier_off(dev);
	return err;
}