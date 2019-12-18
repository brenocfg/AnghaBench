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
struct sbmac_softc {int /*<<< orphan*/  sbm_rxdma; int /*<<< orphan*/  sbm_txdma; int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct sbmac_softc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbdma_emptyring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbmac_set_channel_state (struct sbmac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbmac_state_off ; 

__attribute__((used)) static int sbmac_close(struct net_device *dev)
{
	struct sbmac_softc *sc = netdev_priv(dev);

	napi_disable(&sc->napi);

	phy_stop(sc->phy_dev);

	sbmac_set_channel_state(sc, sbmac_state_off);

	netif_stop_queue(dev);

	if (debug > 1)
		pr_debug("%s: Shutting down ethercard\n", dev->name);

	phy_disconnect(sc->phy_dev);
	sc->phy_dev = NULL;
	free_irq(dev->irq, dev);

	sbdma_emptyring(&(sc->sbm_txdma));
	sbdma_emptyring(&(sc->sbm_rxdma));

	return 0;
}