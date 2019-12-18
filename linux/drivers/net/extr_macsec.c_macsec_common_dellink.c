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
struct net_device {int dummy; } ;
struct macsec_dev {int /*<<< orphan*/  secys; struct net_device* real_dev; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macsec_del_dev (struct macsec_dev*) ; 
 int /*<<< orphan*/  macsec_generation ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 

__attribute__((used)) static void macsec_common_dellink(struct net_device *dev, struct list_head *head)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	struct net_device *real_dev = macsec->real_dev;

	unregister_netdevice_queue(dev, head);
	list_del_rcu(&macsec->secys);
	macsec_del_dev(macsec);
	netdev_upper_dev_unlink(real_dev, dev);

	macsec_generation++;
}