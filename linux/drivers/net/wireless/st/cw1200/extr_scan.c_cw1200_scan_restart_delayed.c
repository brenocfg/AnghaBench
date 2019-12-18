#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cw1200_common {scalar_t__ join_status; int delayed_unjoin; scalar_t__ delayed_link_loss; TYPE_1__* hw; int /*<<< orphan*/  unjoin_work; int /*<<< orphan*/  workqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 scalar_t__ CW1200_JOIN_STATUS_MONITOR ; 
 int /*<<< orphan*/  cw1200_cqm_bssloss_sm (struct cw1200_common*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_enable_listening (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_update_filtering (struct cw1200_common*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static void cw1200_scan_restart_delayed(struct cw1200_common *priv)
{
	/* FW bug: driver has to restart p2p-dev mode after scan. */
	if (priv->join_status == CW1200_JOIN_STATUS_MONITOR) {
		cw1200_enable_listening(priv);
		cw1200_update_filtering(priv);
	}

	if (priv->delayed_unjoin) {
		priv->delayed_unjoin = false;
		if (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
			wsm_unlock_tx(priv);
	} else if (priv->delayed_link_loss) {
			wiphy_dbg(priv->hw->wiphy, "[CQM] Requeue BSS loss.\n");
			priv->delayed_link_loss = 0;
			cw1200_cqm_bssloss_sm(priv, 1, 0, 0);
	}
}