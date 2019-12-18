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
struct jme_adapter {int /*<<< orphan*/  old_cmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  txclean_task; int /*<<< orphan*/  linkch_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_SSET ; 
 int /*<<< orphan*/  JME_NAPI_ENABLE (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_clear_pm_disable_wol (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_link_change_tasklet ; 
 int /*<<< orphan*/  jme_phy_calibration (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_phy_on (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_phy_setEA (struct jme_adapter*) ; 
 int jme_request_irq (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_link (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_phy_processor (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_rx_clean_tasklet ; 
 int /*<<< orphan*/  jme_rx_empty_tasklet ; 
 int /*<<< orphan*/  jme_set_link_ksettings (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_start_irq (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_tx_clean_tasklet ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_open(struct net_device *netdev)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	int rc;

	jme_clear_pm_disable_wol(jme);
	JME_NAPI_ENABLE(jme);

	tasklet_init(&jme->linkch_task, jme_link_change_tasklet,
		     (unsigned long) jme);
	tasklet_init(&jme->txclean_task, jme_tx_clean_tasklet,
		     (unsigned long) jme);
	tasklet_init(&jme->rxclean_task, jme_rx_clean_tasklet,
		     (unsigned long) jme);
	tasklet_init(&jme->rxempty_task, jme_rx_empty_tasklet,
		     (unsigned long) jme);

	rc = jme_request_irq(jme);
	if (rc)
		goto err_out;

	jme_start_irq(jme);

	jme_phy_on(jme);
	if (test_bit(JME_FLAG_SSET, &jme->flags))
		jme_set_link_ksettings(netdev, &jme->old_cmd);
	else
		jme_reset_phy_processor(jme);
	jme_phy_calibration(jme);
	jme_phy_setEA(jme);
	jme_reset_link(jme);

	return 0;

err_out:
	netif_stop_queue(netdev);
	netif_carrier_off(netdev);
	return rc;
}