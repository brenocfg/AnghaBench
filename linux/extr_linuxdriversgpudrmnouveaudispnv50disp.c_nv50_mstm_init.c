#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  mst_state; } ;
struct nv50_mstm {TYPE_1__ mgr; } ;

/* Variables and functions */
 int drm_dp_mst_topology_mgr_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (TYPE_1__*,int) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_mstm_init(struct nv50_mstm *mstm)
{
	int ret;

	if (!mstm || !mstm->mgr.mst_state)
		return;

	ret = drm_dp_mst_topology_mgr_resume(&mstm->mgr);
	if (ret == -1) {
		drm_dp_mst_topology_mgr_set_mst(&mstm->mgr, false);
		drm_kms_helper_hotplug_event(mstm->mgr.dev);
	}
}