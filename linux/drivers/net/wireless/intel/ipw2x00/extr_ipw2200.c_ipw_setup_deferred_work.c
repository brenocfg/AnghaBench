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
struct ipw_priv {int /*<<< orphan*/  irq_tasklet; int /*<<< orphan*/  qos_activate; int /*<<< orphan*/  merge_networks; int /*<<< orphan*/  led_act_off; int /*<<< orphan*/  led_link_off; int /*<<< orphan*/  led_link_on; int /*<<< orphan*/  link_down; int /*<<< orphan*/  link_up; int /*<<< orphan*/  scan_check; int /*<<< orphan*/  roam; int /*<<< orphan*/  abort_scan; int /*<<< orphan*/  gather_stats; int /*<<< orphan*/  scan_event; int /*<<< orphan*/  request_passive_scan; int /*<<< orphan*/  request_direct_scan; int /*<<< orphan*/  request_scan; int /*<<< orphan*/  down; int /*<<< orphan*/  up; int /*<<< orphan*/  rf_kill; int /*<<< orphan*/  adapter_restart; int /*<<< orphan*/  rx_replenish; int /*<<< orphan*/  system_config; int /*<<< orphan*/  disassociate; int /*<<< orphan*/  associate; int /*<<< orphan*/  adhoc_check; int /*<<< orphan*/  wait_state; int /*<<< orphan*/  wait_command_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_bg_abort_scan ; 
 int /*<<< orphan*/  ipw_bg_adapter_restart ; 
 int /*<<< orphan*/  ipw_bg_adhoc_check ; 
 int /*<<< orphan*/  ipw_bg_associate ; 
 int /*<<< orphan*/  ipw_bg_disassociate ; 
 int /*<<< orphan*/  ipw_bg_down ; 
 int /*<<< orphan*/  ipw_bg_gather_stats ; 
 int /*<<< orphan*/  ipw_bg_led_activity_off ; 
 int /*<<< orphan*/  ipw_bg_led_link_off ; 
 int /*<<< orphan*/  ipw_bg_led_link_on ; 
 int /*<<< orphan*/  ipw_bg_link_down ; 
 int /*<<< orphan*/  ipw_bg_link_up ; 
 int /*<<< orphan*/  ipw_bg_qos_activate ; 
 int /*<<< orphan*/  ipw_bg_rf_kill ; 
 int /*<<< orphan*/  ipw_bg_roam ; 
 int /*<<< orphan*/  ipw_bg_rx_queue_replenish ; 
 int /*<<< orphan*/  ipw_bg_scan_check ; 
 int /*<<< orphan*/  ipw_bg_up ; 
 scalar_t__ ipw_irq_tasklet ; 
 int /*<<< orphan*/  ipw_merge_adhoc_network ; 
 int /*<<< orphan*/  ipw_request_direct_scan ; 
 int /*<<< orphan*/  ipw_request_passive_scan ; 
 int /*<<< orphan*/  ipw_request_scan ; 
 int /*<<< orphan*/  ipw_scan_event ; 
 int /*<<< orphan*/  ipw_system_config ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static int ipw_setup_deferred_work(struct ipw_priv *priv)
{
	int ret = 0;

	init_waitqueue_head(&priv->wait_command_queue);
	init_waitqueue_head(&priv->wait_state);

	INIT_DELAYED_WORK(&priv->adhoc_check, ipw_bg_adhoc_check);
	INIT_WORK(&priv->associate, ipw_bg_associate);
	INIT_WORK(&priv->disassociate, ipw_bg_disassociate);
	INIT_WORK(&priv->system_config, ipw_system_config);
	INIT_WORK(&priv->rx_replenish, ipw_bg_rx_queue_replenish);
	INIT_WORK(&priv->adapter_restart, ipw_bg_adapter_restart);
	INIT_DELAYED_WORK(&priv->rf_kill, ipw_bg_rf_kill);
	INIT_WORK(&priv->up, ipw_bg_up);
	INIT_WORK(&priv->down, ipw_bg_down);
	INIT_DELAYED_WORK(&priv->request_scan, ipw_request_scan);
	INIT_DELAYED_WORK(&priv->request_direct_scan, ipw_request_direct_scan);
	INIT_DELAYED_WORK(&priv->request_passive_scan, ipw_request_passive_scan);
	INIT_DELAYED_WORK(&priv->scan_event, ipw_scan_event);
	INIT_DELAYED_WORK(&priv->gather_stats, ipw_bg_gather_stats);
	INIT_WORK(&priv->abort_scan, ipw_bg_abort_scan);
	INIT_WORK(&priv->roam, ipw_bg_roam);
	INIT_DELAYED_WORK(&priv->scan_check, ipw_bg_scan_check);
	INIT_WORK(&priv->link_up, ipw_bg_link_up);
	INIT_WORK(&priv->link_down, ipw_bg_link_down);
	INIT_DELAYED_WORK(&priv->led_link_on, ipw_bg_led_link_on);
	INIT_DELAYED_WORK(&priv->led_link_off, ipw_bg_led_link_off);
	INIT_DELAYED_WORK(&priv->led_act_off, ipw_bg_led_activity_off);
	INIT_WORK(&priv->merge_networks, ipw_merge_adhoc_network);

#ifdef CONFIG_IPW2200_QOS
	INIT_WORK(&priv->qos_activate, ipw_bg_qos_activate);
#endif				/* CONFIG_IPW2200_QOS */

	tasklet_init(&priv->irq_tasklet, (void (*)(unsigned long))
		     ipw_irq_tasklet, (unsigned long)priv);

	return ret;
}