#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_dp_mst_topology_mgr {int max_payloads; int /*<<< orphan*/  payload_lock; TYPE_3__** proposed_vcpis; TYPE_2__* payloads; } ;
struct dp_mst_stream_allocation_table {size_t stream_count; struct dp_mst_stream_allocation* stream_allocations; } ;
struct dp_mst_stream_allocation {scalar_t__ slot_count; int /*<<< orphan*/  vcp_id; } ;
struct amdgpu_dm_connector {TYPE_1__* mst_port; } ;
struct TYPE_6__ {int /*<<< orphan*/  vcpi; } ;
struct TYPE_5__ {scalar_t__ num_slots; scalar_t__ payload_state; } ;
struct TYPE_4__ {struct drm_dp_mst_topology_mgr mst_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DP_PAYLOAD_DELETE_LOCAL ; 
 scalar_t__ DP_PAYLOAD_LOCAL ; 
 scalar_t__ DP_PAYLOAD_REMOTE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_payload_table(
		struct amdgpu_dm_connector *aconnector,
		struct dp_mst_stream_allocation_table *proposed_table)
{
	int i;
	struct drm_dp_mst_topology_mgr *mst_mgr =
			&aconnector->mst_port->mst_mgr;

	mutex_lock(&mst_mgr->payload_lock);

	proposed_table->stream_count = 0;

	/* number of active streams */
	for (i = 0; i < mst_mgr->max_payloads; i++) {
		if (mst_mgr->payloads[i].num_slots == 0)
			break; /* end of vcp_id table */

		ASSERT(mst_mgr->payloads[i].payload_state !=
				DP_PAYLOAD_DELETE_LOCAL);

		if (mst_mgr->payloads[i].payload_state == DP_PAYLOAD_LOCAL ||
			mst_mgr->payloads[i].payload_state ==
					DP_PAYLOAD_REMOTE) {

			struct dp_mst_stream_allocation *sa =
					&proposed_table->stream_allocations[
						proposed_table->stream_count];

			sa->slot_count = mst_mgr->payloads[i].num_slots;
			sa->vcp_id = mst_mgr->proposed_vcpis[i]->vcpi;
			proposed_table->stream_count++;
		}
	}

	mutex_unlock(&mst_mgr->payload_lock);
}