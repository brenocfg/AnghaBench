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
struct bcmgenet_priv {struct net_device* dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RBUF_STATUS ; 
 int RBUF_STATUS_WOL ; 
 int bcmgenet_rbuf_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_crit (struct net_device*,char*) ; 

__attribute__((used)) static int bcmgenet_poll_wol_status(struct bcmgenet_priv *priv)
{
	struct net_device *dev = priv->dev;
	int retries = 0;

	while (!(bcmgenet_rbuf_readl(priv, RBUF_STATUS)
		& RBUF_STATUS_WOL)) {
		retries++;
		if (retries > 5) {
			netdev_crit(dev, "polling wol mode timeout\n");
			return -ETIMEDOUT;
		}
		mdelay(1);
	}

	return retries;
}