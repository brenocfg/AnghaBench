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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;
struct macsec_dev {struct net_device* real_dev; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int IFF_UP ; 
 int dev_uc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 

__attribute__((used)) static int macsec_set_mac_address(struct net_device *dev, void *p)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	struct net_device *real_dev = macsec->real_dev;
	struct sockaddr *addr = p;
	int err;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (!(dev->flags & IFF_UP))
		goto out;

	err = dev_uc_add(real_dev, addr->sa_data);
	if (err < 0)
		return err;

	dev_uc_del(real_dev, dev->dev_addr);

out:
	ether_addr_copy(dev->dev_addr, addr->sa_data);
	return 0;
}