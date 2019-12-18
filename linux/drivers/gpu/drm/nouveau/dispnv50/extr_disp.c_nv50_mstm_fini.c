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
struct TYPE_2__ {scalar_t__ mst_state; } ;
struct nv50_mstm {TYPE_1__ mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_suspend (TYPE_1__*) ; 

__attribute__((used)) static void
nv50_mstm_fini(struct nv50_mstm *mstm)
{
	if (mstm && mstm->mgr.mst_state)
		drm_dp_mst_topology_mgr_suspend(&mstm->mgr);
}