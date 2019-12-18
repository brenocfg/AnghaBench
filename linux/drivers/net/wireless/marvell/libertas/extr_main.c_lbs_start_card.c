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
struct net_device {int /*<<< orphan*/  name; } ;
struct lbs_private {struct net_device* dev; } ;

/* Variables and functions */
 int lbs_cfg_register (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_debugfs_init_one (struct lbs_private*,struct net_device*) ; 
 int /*<<< orphan*/  lbs_disablemesh ; 
 int /*<<< orphan*/  lbs_init_mesh (struct lbs_private*) ; 
 scalar_t__ lbs_mesh_activated (struct lbs_private*) ; 
 int lbs_setup_firmware (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_start_mesh (struct lbs_private*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int lbs_start_card(struct lbs_private *priv)
{
	struct net_device *dev = priv->dev;
	int ret;

	/* poke the firmware */
	ret = lbs_setup_firmware(priv);
	if (ret)
		goto done;

	if (!lbs_disablemesh)
		lbs_init_mesh(priv);
	else
		pr_info("%s: mesh disabled\n", dev->name);

	ret = lbs_cfg_register(priv);
	if (ret) {
		pr_err("cannot register device\n");
		goto done;
	}

	if (lbs_mesh_activated(priv))
		lbs_start_mesh(priv);

	lbs_debugfs_init_one(priv, dev);

	netdev_info(dev, "Marvell WLAN 802.11 adapter\n");

	ret = 0;

done:
	return ret;
}