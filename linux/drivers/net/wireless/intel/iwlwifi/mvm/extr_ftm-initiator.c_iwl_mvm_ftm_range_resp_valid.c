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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {TYPE_2__* req; } ;
struct iwl_mvm {TYPE_1__ ftm_initiator; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {scalar_t__ n_peers; scalar_t__ cookie; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_ftm_range_resp_valid(struct iwl_mvm *mvm, u8 request_id,
					u8 num_of_aps)
{
	lockdep_assert_held(&mvm->mutex);

	if (request_id != (u8)mvm->ftm_initiator.req->cookie) {
		IWL_ERR(mvm, "Request ID mismatch, got %u, active %u\n",
			request_id, (u8)mvm->ftm_initiator.req->cookie);
		return -EINVAL;
	}

	if (num_of_aps > mvm->ftm_initiator.req->n_peers) {
		IWL_ERR(mvm, "FTM range response invalid\n");
		return -EINVAL;
	}

	return 0;
}