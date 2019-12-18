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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct ath10k_mac_change_chanctx_arg {scalar_t__ ctx; int /*<<< orphan*/  n_vifs; } ;

/* Variables and functions */
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath10k_mac_change_chanctx_cnt_iter(void *data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct ath10k_mac_change_chanctx_arg *arg = data;

	if (rcu_access_pointer(vif->chanctx_conf) != arg->ctx)
		return;

	arg->n_vifs++;
}