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
struct net_device {char* name; int /*<<< orphan*/  dev; } ;
struct can_priv {int /*<<< orphan*/  rxtx_led_trig; int /*<<< orphan*/  rxtx_led_trig_name; int /*<<< orphan*/  rx_led_trig; int /*<<< orphan*/  rx_led_trig_name; int /*<<< orphan*/  tx_led_trig; int /*<<< orphan*/  tx_led_trig_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  can_led_release ; 
 int /*<<< orphan*/  devres_add (int /*<<< orphan*/ *,void*) ; 
 void* devres_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_trigger_register_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

void devm_can_led_init(struct net_device *netdev)
{
	struct can_priv *priv = netdev_priv(netdev);
	void *res;

	res = devres_alloc(can_led_release, 0, GFP_KERNEL);
	if (!res) {
		netdev_err(netdev, "cannot register LED triggers\n");
		return;
	}

	snprintf(priv->tx_led_trig_name, sizeof(priv->tx_led_trig_name),
		 "%s-tx", netdev->name);
	snprintf(priv->rx_led_trig_name, sizeof(priv->rx_led_trig_name),
		 "%s-rx", netdev->name);
	snprintf(priv->rxtx_led_trig_name, sizeof(priv->rxtx_led_trig_name),
		 "%s-rxtx", netdev->name);

	led_trigger_register_simple(priv->tx_led_trig_name,
				    &priv->tx_led_trig);
	led_trigger_register_simple(priv->rx_led_trig_name,
				    &priv->rx_led_trig);
	led_trigger_register_simple(priv->rxtx_led_trig_name,
				    &priv->rxtx_led_trig);

	devres_add(&netdev->dev, res);
}