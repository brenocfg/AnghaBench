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
struct dev_priv {int media_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  link ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct dev_priv*,int /*<<< orphan*/ ,struct net_device*,char*,char*) ; 

__attribute__((used)) static void set_media_state(struct net_device *dev, int media_state)
{
	struct dev_priv *priv = netdev_priv(dev);

	if (media_state == priv->media_state)
		netif_carrier_on(dev);
	else
		netif_carrier_off(dev);
	netif_info(priv, link, dev, "link %s\n",
		   media_state == priv->media_state ? "on" : "off");
}