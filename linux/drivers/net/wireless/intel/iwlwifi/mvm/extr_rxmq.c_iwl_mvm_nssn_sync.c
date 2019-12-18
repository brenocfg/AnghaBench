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
struct napi_struct {int dummy; } ;
struct iwl_mvm_nssn_sync_data {int /*<<< orphan*/  nssn; int /*<<< orphan*/  baid; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_RELEASE_FROM_RSS_SYNC ; 
 int /*<<< orphan*/  iwl_mvm_release_frames_from_notif (struct iwl_mvm*,struct napi_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_nssn_sync(struct iwl_mvm *mvm,
			      struct napi_struct *napi, int queue,
			      const struct iwl_mvm_nssn_sync_data *data)
{
	iwl_mvm_release_frames_from_notif(mvm, napi, data->baid,
					  data->nssn, queue,
					  IWL_MVM_RELEASE_FROM_RSS_SYNC);
}