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
struct net_device {scalar_t__ mtu; } ;
struct jme_adapter {scalar_t__ old_mtu; int /*<<< orphan*/  link_changing; int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  txclean_task; int /*<<< orphan*/  flags; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr ; 
 scalar_t__ jme_check_link (struct net_device*,int) ; 
 int /*<<< orphan*/  jme_disable_rx_engine (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_disable_tx_engine (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_enable_rx_engine (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_enable_tx_engine (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_free_rx_resources (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_free_tx_resources (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_interrupt_mode (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_polling_mode (struct jme_adapter*) ; 
 scalar_t__ jme_pseudo_hotplug_enabled (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_mac_processor (struct jme_adapter*) ; 
 int jme_setup_rx_resources (struct jme_adapter*) ; 
 int jme_setup_tx_resources (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_start_pcc_timer (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_start_shutdown_timer (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_stop_pcc_timer (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_stop_shutdown_timer (struct jme_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct jme_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_link_change_tasklet(unsigned long arg)
{
	struct jme_adapter *jme = (struct jme_adapter *)arg;
	struct net_device *netdev = jme->dev;
	int rc;

	while (!atomic_dec_and_test(&jme->link_changing)) {
		atomic_inc(&jme->link_changing);
		netif_info(jme, intr, jme->dev, "Get link change lock failed\n");
		while (atomic_read(&jme->link_changing) != 1)
			netif_info(jme, intr, jme->dev, "Waiting link change lock\n");
	}

	if (jme_check_link(netdev, 1) && jme->old_mtu == netdev->mtu)
		goto out;

	jme->old_mtu = netdev->mtu;
	netif_stop_queue(netdev);
	if (jme_pseudo_hotplug_enabled(jme))
		jme_stop_shutdown_timer(jme);

	jme_stop_pcc_timer(jme);
	tasklet_disable(&jme->txclean_task);
	tasklet_disable(&jme->rxclean_task);
	tasklet_disable(&jme->rxempty_task);

	if (netif_carrier_ok(netdev)) {
		jme_disable_rx_engine(jme);
		jme_disable_tx_engine(jme);
		jme_reset_mac_processor(jme);
		jme_free_rx_resources(jme);
		jme_free_tx_resources(jme);

		if (test_bit(JME_FLAG_POLL, &jme->flags))
			jme_polling_mode(jme);

		netif_carrier_off(netdev);
	}

	jme_check_link(netdev, 0);
	if (netif_carrier_ok(netdev)) {
		rc = jme_setup_rx_resources(jme);
		if (rc) {
			pr_err("Allocating resources for RX error, Device STOPPED!\n");
			goto out_enable_tasklet;
		}

		rc = jme_setup_tx_resources(jme);
		if (rc) {
			pr_err("Allocating resources for TX error, Device STOPPED!\n");
			goto err_out_free_rx_resources;
		}

		jme_enable_rx_engine(jme);
		jme_enable_tx_engine(jme);

		netif_start_queue(netdev);

		if (test_bit(JME_FLAG_POLL, &jme->flags))
			jme_interrupt_mode(jme);

		jme_start_pcc_timer(jme);
	} else if (jme_pseudo_hotplug_enabled(jme)) {
		jme_start_shutdown_timer(jme);
	}

	goto out_enable_tasklet;

err_out_free_rx_resources:
	jme_free_rx_resources(jme);
out_enable_tasklet:
	tasklet_enable(&jme->txclean_task);
	tasklet_enable(&jme->rxclean_task);
	tasklet_enable(&jme->rxempty_task);
out:
	atomic_inc(&jme->link_changing);
}