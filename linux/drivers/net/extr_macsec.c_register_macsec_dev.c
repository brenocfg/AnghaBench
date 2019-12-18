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
struct macsec_rxh_data {int /*<<< orphan*/  secys; } ;
struct macsec_dev {int /*<<< orphan*/  secys; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct macsec_rxh_data*) ; 
 struct macsec_rxh_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct macsec_rxh_data* macsec_data_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  macsec_handle_frame ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct macsec_rxh_data*) ; 

__attribute__((used)) static int register_macsec_dev(struct net_device *real_dev,
			       struct net_device *dev)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	struct macsec_rxh_data *rxd = macsec_data_rtnl(real_dev);

	if (!rxd) {
		int err;

		rxd = kmalloc(sizeof(*rxd), GFP_KERNEL);
		if (!rxd)
			return -ENOMEM;

		INIT_LIST_HEAD(&rxd->secys);

		err = netdev_rx_handler_register(real_dev, macsec_handle_frame,
						 rxd);
		if (err < 0) {
			kfree(rxd);
			return err;
		}
	}

	list_add_tail_rcu(&macsec->secys, &rxd->secys);
	return 0;
}