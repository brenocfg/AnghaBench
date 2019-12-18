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
struct rs_tx_column {int dummy; } ;
struct rs_rate {int dummy; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;

/* Variables and functions */

__attribute__((used)) static bool rs_siso_allow(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			  struct rs_rate *rate,
			  const struct rs_tx_column *next_col)
{
	if (!sta->ht_cap.ht_supported)
		return false;

	return true;
}