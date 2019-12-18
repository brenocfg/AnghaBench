#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * function; } ;
struct tlan_priv {TYPE_1__ timer; TYPE_1__ media_timer; } ;
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_HC_AD_RST ; 
 scalar_t__ TLAN_HOST_CMD ; 
 int /*<<< orphan*/  TLAN_RECORD ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tlan_read_and_clear_stats (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_reset_adapter (struct net_device*) ; 

__attribute__((used)) static void tlan_stop(struct net_device *dev)
{
	struct tlan_priv *priv = netdev_priv(dev);

	del_timer_sync(&priv->media_timer);
	tlan_read_and_clear_stats(dev, TLAN_RECORD);
	outl(TLAN_HC_AD_RST, dev->base_addr + TLAN_HOST_CMD);
	/* Reset and power down phy */
	tlan_reset_adapter(dev);
	if (priv->timer.function != NULL) {
		del_timer_sync(&priv->timer);
		priv->timer.function = NULL;
	}
}