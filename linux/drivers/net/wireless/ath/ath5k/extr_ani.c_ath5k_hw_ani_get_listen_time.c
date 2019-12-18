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
struct ath_common {int /*<<< orphan*/  cc_lock; int /*<<< orphan*/  cc_ani; } ;
struct ath5k_hw {int dummy; } ;
struct ath5k_ani_state {int /*<<< orphan*/  last_cc; } ;

/* Variables and functions */
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath_hw_cycle_counters_update (struct ath_common*) ; 
 int ath_hw_get_listen_time (struct ath_common*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath5k_hw_ani_get_listen_time(struct ath5k_hw *ah, struct ath5k_ani_state *as)
{
	struct ath_common *common = ath5k_hw_common(ah);
	int listen;

	spin_lock_bh(&common->cc_lock);

	ath_hw_cycle_counters_update(common);
	memcpy(&as->last_cc, &common->cc_ani, sizeof(as->last_cc));

	/* clears common->cc_ani */
	listen = ath_hw_get_listen_time(common);

	spin_unlock_bh(&common->cc_lock);

	return listen;
}