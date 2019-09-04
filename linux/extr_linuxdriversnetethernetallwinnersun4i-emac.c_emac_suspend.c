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
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  emac_shutdown (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int emac_suspend(struct platform_device *dev, pm_message_t state)
{
	struct net_device *ndev = platform_get_drvdata(dev);

	netif_carrier_off(ndev);
	netif_device_detach(ndev);
	emac_shutdown(ndev);

	return 0;
}