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
struct sk_buff {int dummy; } ;
struct cw1200_common {int bss_loss_state; int /*<<< orphan*/  hw; TYPE_1__* vif; int /*<<< orphan*/  bss_loss_work; int /*<<< orphan*/  bss_params_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  tx_lock; scalar_t__ delayed_unjoin; scalar_t__ delayed_link_loss; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_bssloss_mitigation ; 
 int /*<<< orphan*/  cw1200_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* ieee80211_nullfunc_get (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __cw1200_cqm_bssloss_sm(struct cw1200_common *priv,
			     int init, int good, int bad)
{
	int tx = 0;

	priv->delayed_link_loss = 0;
	cancel_work_sync(&priv->bss_params_work);

	pr_debug("[STA] CQM BSSLOSS_SM: state: %d init %d good %d bad: %d txlock: %d uj: %d\n",
		 priv->bss_loss_state,
		 init, good, bad,
		 atomic_read(&priv->tx_lock),
		 priv->delayed_unjoin);

	/* If we have a pending unjoin */
	if (priv->delayed_unjoin)
		return;

	if (init) {
		queue_delayed_work(priv->workqueue,
				   &priv->bss_loss_work,
				   HZ);
		priv->bss_loss_state = 0;

		/* Skip the confimration procedure in P2P case */
		if (!priv->vif->p2p && !atomic_read(&priv->tx_lock))
			tx = 1;
	} else if (good) {
		cancel_delayed_work_sync(&priv->bss_loss_work);
		priv->bss_loss_state = 0;
		queue_work(priv->workqueue, &priv->bss_params_work);
	} else if (bad) {
		/* XXX Should we just keep going until we time out? */
		if (priv->bss_loss_state < 3)
			tx = 1;
	} else {
		cancel_delayed_work_sync(&priv->bss_loss_work);
		priv->bss_loss_state = 0;
	}

	/* Bypass mitigation if it's disabled */
	if (!cw1200_bssloss_mitigation)
		tx = 0;

	/* Spit out a NULL packet to our AP if necessary */
	if (tx) {
		struct sk_buff *skb;

		priv->bss_loss_state++;

		skb = ieee80211_nullfunc_get(priv->hw, priv->vif, false);
		WARN_ON(!skb);
		if (skb)
			cw1200_tx(priv->hw, NULL, skb);
	}
}