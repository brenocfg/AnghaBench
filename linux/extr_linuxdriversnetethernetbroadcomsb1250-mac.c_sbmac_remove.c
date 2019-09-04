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
struct sbmac_softc {int /*<<< orphan*/  sbm_base; int /*<<< orphan*/  mii_bus; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct sbmac_softc* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sbmac_uninitctx (struct sbmac_softc*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int sbmac_remove(struct platform_device *pldev)
{
	struct net_device *dev = platform_get_drvdata(pldev);
	struct sbmac_softc *sc = netdev_priv(dev);

	unregister_netdev(dev);
	sbmac_uninitctx(sc);
	mdiobus_unregister(sc->mii_bus);
	mdiobus_free(sc->mii_bus);
	iounmap(sc->sbm_base);
	free_netdev(dev);

	return 0;
}