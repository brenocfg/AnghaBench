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
struct ipw_priv {int status; int /*<<< orphan*/  scan_event; int /*<<< orphan*/  request_scan; int /*<<< orphan*/  gather_stats; int /*<<< orphan*/  adhoc_check; int /*<<< orphan*/  request_passive_scan; int /*<<< orphan*/  request_direct_scan; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_led_link_down (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_reset_stats (struct ipw_priv*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct ipw_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_link_down(struct ipw_priv *priv)
{
	ipw_led_link_down(priv);
	netif_carrier_off(priv->net_dev);
	notify_wx_assoc_event(priv);

	/* Cancel any queued work ... */
	cancel_delayed_work(&priv->request_scan);
	cancel_delayed_work(&priv->request_direct_scan);
	cancel_delayed_work(&priv->request_passive_scan);
	cancel_delayed_work(&priv->adhoc_check);
	cancel_delayed_work(&priv->gather_stats);

	ipw_reset_stats(priv);

	if (!(priv->status & STATUS_EXIT_PENDING)) {
		/* Queue up another scan... */
		schedule_delayed_work(&priv->request_scan, 0);
	} else
		cancel_delayed_work(&priv->scan_event);
}