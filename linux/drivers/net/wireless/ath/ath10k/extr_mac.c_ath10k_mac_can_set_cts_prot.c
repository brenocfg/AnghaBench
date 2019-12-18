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
struct ath10k_vif {int /*<<< orphan*/  is_started; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath10k_mac_can_set_cts_prot(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;

	lockdep_assert_held(&ar->conf_mutex);

	if (!arvif->is_started) {
		ath10k_dbg(ar, ATH10K_DBG_MAC, "defer cts setup, vdev is not ready yet\n");
		return false;
	}

	return true;
}