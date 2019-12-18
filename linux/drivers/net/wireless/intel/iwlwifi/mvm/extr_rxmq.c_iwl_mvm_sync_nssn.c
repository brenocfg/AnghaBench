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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  nssn; int /*<<< orphan*/  baid; } ;
struct TYPE_3__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  type; } ;
struct iwl_mvm_rss_sync_notif {TYPE_2__ nssn_sync; TYPE_1__ metadata; } ;
struct iwl_mvm {int dummy; } ;
typedef  int /*<<< orphan*/  notif ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_RXQ_NSSN_SYNC ; 
 int /*<<< orphan*/  iwl_mvm_sync_rx_queues_internal (struct iwl_mvm*,void*,int) ; 

__attribute__((used)) static void iwl_mvm_sync_nssn(struct iwl_mvm *mvm, u8 baid, u16 nssn)
{
	struct iwl_mvm_rss_sync_notif notif = {
		.metadata.type = IWL_MVM_RXQ_NSSN_SYNC,
		.metadata.sync = 0,
		.nssn_sync.baid = baid,
		.nssn_sync.nssn = nssn,
	};

	iwl_mvm_sync_rx_queues_internal(mvm, (void *)&notif, sizeof(notif));
}