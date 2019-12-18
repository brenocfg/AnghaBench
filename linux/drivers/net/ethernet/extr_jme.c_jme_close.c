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
struct jme_adapter {scalar_t__ phylink; int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  txclean_task; int /*<<< orphan*/  linkch_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_NAPI_DISABLE (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_disable_rx_engine (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_disable_tx_engine (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_free_irq (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_free_rx_resources (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_free_tx_resources (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_phy_off (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_mac_processor (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_stop_irq (struct jme_adapter*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_close(struct net_device *netdev)
{
	struct jme_adapter *jme = netdev_priv(netdev);

	netif_stop_queue(netdev);
	netif_carrier_off(netdev);

	jme_stop_irq(jme);
	jme_free_irq(jme);

	JME_NAPI_DISABLE(jme);

	tasklet_kill(&jme->linkch_task);
	tasklet_kill(&jme->txclean_task);
	tasklet_kill(&jme->rxclean_task);
	tasklet_kill(&jme->rxempty_task);

	jme_disable_rx_engine(jme);
	jme_disable_tx_engine(jme);
	jme_reset_mac_processor(jme);
	jme_free_rx_resources(jme);
	jme_free_tx_resources(jme);
	jme->phylink = 0;
	jme_phy_off(jme);

	return 0;
}