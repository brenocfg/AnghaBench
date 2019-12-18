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
struct lbs_private {scalar_t__ psmode; scalar_t__ psstate; int surpriseremoved; int /*<<< orphan*/  main_thread; int /*<<< orphan*/  host_sleep_q; scalar_t__ is_host_sleep_activated; scalar_t__ is_host_sleep_configured; int /*<<< orphan*/  ds_awake_q; scalar_t__ is_deep_sleep; int /*<<< orphan*/  work_thread; scalar_t__ wiphy_registered; struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ LBS802_11POWERMODECAM ; 
 scalar_t__ LBS802_11POWERMODEMAX_PSP ; 
 int /*<<< orphan*/  PS_MODE_ACTION_EXIT_PS ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_cfg_free (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_main (char*) ; 
 int /*<<< orphan*/  lbs_free_adapter (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_remove_mesh (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_scan_deinit (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_set_ps_mode (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lbs_wait_for_firmware_load (struct lbs_private*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void lbs_remove_card(struct lbs_private *priv)
{
	struct net_device *dev = priv->dev;

	lbs_remove_mesh(priv);

	if (priv->wiphy_registered)
		lbs_scan_deinit(priv);

	lbs_wait_for_firmware_load(priv);

	/* worker thread destruction blocks on the in-flight command which
	 * should have been cleared already in lbs_stop_card().
	 */
	lbs_deb_main("destroying worker thread\n");
	destroy_workqueue(priv->work_thread);
	lbs_deb_main("done destroying worker thread\n");

	if (priv->psmode == LBS802_11POWERMODEMAX_PSP) {
		priv->psmode = LBS802_11POWERMODECAM;
		/* no need to wakeup if already woken up,
		 * on suspend, this exit ps command is not processed
		 * the driver hangs
		 */
		if (priv->psstate != PS_STATE_FULL_POWER)
			lbs_set_ps_mode(priv, PS_MODE_ACTION_EXIT_PS, true);
	}

	if (priv->is_deep_sleep) {
		priv->is_deep_sleep = 0;
		wake_up_interruptible(&priv->ds_awake_q);
	}

	priv->is_host_sleep_configured = 0;
	priv->is_host_sleep_activated = 0;
	wake_up_interruptible(&priv->host_sleep_q);

	/* Stop the thread servicing the interrupts */
	priv->surpriseremoved = 1;
	kthread_stop(priv->main_thread);

	lbs_free_adapter(priv);
	lbs_cfg_free(priv);
	free_netdev(dev);
}