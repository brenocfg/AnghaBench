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
struct iwl_mvm_tx_resp_v3 {struct agg_tx_status* status; } ;
struct agg_tx_status {int dummy; } ;
struct iwl_mvm_tx_resp {struct agg_tx_status status; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 

__attribute__((used)) static inline struct agg_tx_status *
iwl_mvm_get_agg_status(struct iwl_mvm *mvm, void *tx_resp)
{
	if (iwl_mvm_has_new_tx_api(mvm))
		return &((struct iwl_mvm_tx_resp *)tx_resp)->status;
	else
		return ((struct iwl_mvm_tx_resp_v3 *)tx_resp)->status;
}