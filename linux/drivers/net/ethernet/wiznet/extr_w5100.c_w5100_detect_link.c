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
struct w5100_priv {int /*<<< orphan*/  link_gpio; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct w5100_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static irqreturn_t w5100_detect_link(int irq, void *ndev_instance)
{
	struct net_device *ndev = ndev_instance;
	struct w5100_priv *priv = netdev_priv(ndev);

	if (netif_running(ndev)) {
		if (gpio_get_value(priv->link_gpio) != 0) {
			netif_info(priv, link, ndev, "link is up\n");
			netif_carrier_on(ndev);
		} else {
			netif_info(priv, link, ndev, "link is down\n");
			netif_carrier_off(ndev);
		}
	}

	return IRQ_HANDLED;
}