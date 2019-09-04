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
struct drm_dp_mst_topology_mgr {int max_payloads; int /*<<< orphan*/  payload_lock; int /*<<< orphan*/  payload_mask; TYPE_1__** proposed_vcpis; int /*<<< orphan*/  vcpi_mask; } ;
struct TYPE_2__ {int vcpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_dp_mst_put_payload_id(struct drm_dp_mst_topology_mgr *mgr,
				      int vcpi)
{
	int i;
	if (vcpi == 0)
		return;

	mutex_lock(&mgr->payload_lock);
	DRM_DEBUG_KMS("putting payload %d\n", vcpi);
	clear_bit(vcpi - 1, &mgr->vcpi_mask);

	for (i = 0; i < mgr->max_payloads; i++) {
		if (mgr->proposed_vcpis[i])
			if (mgr->proposed_vcpis[i]->vcpi == vcpi) {
				mgr->proposed_vcpis[i] = NULL;
				clear_bit(i + 1, &mgr->payload_mask);
			}
	}
	mutex_unlock(&mgr->payload_lock);
}