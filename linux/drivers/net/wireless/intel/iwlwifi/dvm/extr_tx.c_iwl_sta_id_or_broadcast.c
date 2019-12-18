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
struct iwl_rxon_context {int bcast_sta_id; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int IWL_INVALID_STATION ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int iwl_sta_id (struct ieee80211_sta*) ; 

__attribute__((used)) static int iwl_sta_id_or_broadcast(struct iwl_rxon_context *context,
				   struct ieee80211_sta *sta)
{
	int sta_id;

	if (!sta)
		return context->bcast_sta_id;

	sta_id = iwl_sta_id(sta);

	/*
	 * mac80211 should not be passing a partially
	 * initialised station!
	 */
	WARN_ON(sta_id == IWL_INVALID_STATION);

	return sta_id;
}