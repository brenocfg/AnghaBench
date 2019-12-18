#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_vif_chanctx_switch {TYPE_1__* new_ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/ * chan; } ;
struct ieee80211_chanctx_conf {TYPE_2__ def; } ;
struct cfg80211_chan_def {int /*<<< orphan*/ * chan; } ;
struct ath10k {scalar_t__ state; int /*<<< orphan*/ * rx_channel; int /*<<< orphan*/  hw; int /*<<< orphan*/  data_lock; int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_3__ {struct cfg80211_chan_def def; } ;

/* Variables and functions */
 scalar_t__ ATH10K_STATE_RESTARTED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_mac_get_any_chandef_iter ; 
 int ath10k_mac_num_chanctxs (struct ath10k*) ; 
 int /*<<< orphan*/  ieee80211_iter_chan_contexts_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_chan_def**) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void
ath10k_mac_update_rx_channel(struct ath10k *ar,
			     struct ieee80211_chanctx_conf *ctx,
			     struct ieee80211_vif_chanctx_switch *vifs,
			     int n_vifs)
{
	struct cfg80211_chan_def *def = NULL;

	/* Both locks are required because ar->rx_channel is modified. This
	 * allows readers to hold either lock.
	 */
	lockdep_assert_held(&ar->conf_mutex);
	lockdep_assert_held(&ar->data_lock);

	WARN_ON(ctx && vifs);
	WARN_ON(vifs && !n_vifs);

	/* FIXME: Sort of an optimization and a workaround. Peers and vifs are
	 * on a linked list now. Doing a lookup peer -> vif -> chanctx for each
	 * ppdu on Rx may reduce performance on low-end systems. It should be
	 * possible to make tables/hashmaps to speed the lookup up (be vary of
	 * cpu data cache lines though regarding sizes) but to keep the initial
	 * implementation simple and less intrusive fallback to the slow lookup
	 * only for multi-channel cases. Single-channel cases will remain to
	 * use the old channel derival and thus performance should not be
	 * affected much.
	 */
	rcu_read_lock();
	if (!ctx && ath10k_mac_num_chanctxs(ar) == 1) {
		ieee80211_iter_chan_contexts_atomic(ar->hw,
						    ath10k_mac_get_any_chandef_iter,
						    &def);

		if (vifs)
			def = &vifs[0].new_ctx->def;

		ar->rx_channel = def->chan;
	} else if ((ctx && ath10k_mac_num_chanctxs(ar) == 0) ||
		   (ctx && (ar->state == ATH10K_STATE_RESTARTED))) {
		/* During driver restart due to firmware assert, since mac80211
		 * already has valid channel context for given radio, channel
		 * context iteration return num_chanctx > 0. So fix rx_channel
		 * when restart is in progress.
		 */
		ar->rx_channel = ctx->def.chan;
	} else {
		ar->rx_channel = NULL;
	}
	rcu_read_unlock();
}