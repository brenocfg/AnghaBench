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
struct net_device {int /*<<< orphan*/  dev; } ;
struct arcnet_local {int /*<<< orphan*/  recon_led_trig; int /*<<< orphan*/  recon_led_trig_name; int /*<<< orphan*/  tx_led_trig; int /*<<< orphan*/  tx_led_trig_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  arcnet_led_release ; 
 int /*<<< orphan*/  devres_add (int /*<<< orphan*/ *,void*) ; 
 void* devres_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_trigger_register_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

void devm_arcnet_led_init(struct net_device *netdev, int index, int subid)
{
	struct arcnet_local *lp = netdev_priv(netdev);
	void *res;

	res = devres_alloc(arcnet_led_release, 0, GFP_KERNEL);
	if (!res) {
		netdev_err(netdev, "cannot register LED triggers\n");
		return;
	}

	snprintf(lp->tx_led_trig_name, sizeof(lp->tx_led_trig_name),
		 "arc%d-%d-tx", index, subid);
	snprintf(lp->recon_led_trig_name, sizeof(lp->recon_led_trig_name),
		 "arc%d-%d-recon", index, subid);

	led_trigger_register_simple(lp->tx_led_trig_name,
				    &lp->tx_led_trig);
	led_trigger_register_simple(lp->recon_led_trig_name,
				    &lp->recon_led_trig);

	devres_add(&netdev->dev, res);
}