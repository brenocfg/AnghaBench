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
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_common {int /*<<< orphan*/  pm_state; int /*<<< orphan*/  tx_queue_stats; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/ * sdd; int /*<<< orphan*/ * workqueue; int /*<<< orphan*/  wsm_cmd_buf; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  mcast_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_debug_release (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_pm_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_queue_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_queue_stats_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_unregister_bh (struct cw1200_common*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_buf_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cw1200_unregister_common(struct ieee80211_hw *dev)
{
	struct cw1200_common *priv = dev->priv;
	int i;

	ieee80211_unregister_hw(dev);

	del_timer_sync(&priv->mcast_timeout);
	cw1200_unregister_bh(priv);

	cw1200_debug_release(priv);

	mutex_destroy(&priv->conf_mutex);

	wsm_buf_deinit(&priv->wsm_cmd_buf);

	destroy_workqueue(priv->workqueue);
	priv->workqueue = NULL;

	if (priv->sdd) {
		release_firmware(priv->sdd);
		priv->sdd = NULL;
	}

	for (i = 0; i < 4; ++i)
		cw1200_queue_deinit(&priv->tx_queue[i]);

	cw1200_queue_stats_deinit(&priv->tx_queue_stats);
#ifdef CONFIG_PM
	cw1200_pm_deinit(&priv->pm_state);
#endif
}