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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int flags; } ;
struct emac_adapter {int dummy; } ;

/* Variables and functions */
 int IFF_UP ; 
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emac_mac_reset (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_close (struct emac_adapter*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void emac_shutdown(struct platform_device *pdev)
{
	struct net_device *netdev = dev_get_drvdata(&pdev->dev);
	struct emac_adapter *adpt = netdev_priv(netdev);

	if (netdev->flags & IFF_UP) {
		/* Closing the SGMII turns off its interrupts */
		emac_sgmii_close(adpt);

		/* Resetting the MAC turns off all DMA and its interrupts */
		emac_mac_reset(adpt);
	}
}