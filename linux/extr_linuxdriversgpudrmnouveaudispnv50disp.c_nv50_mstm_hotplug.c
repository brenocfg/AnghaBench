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
struct nv50_mstm {TYPE_3__* outp; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (int /*<<< orphan*/ ) ; 
 struct nv50_mstm* nv50_mstm (struct drm_dp_mst_topology_mgr*) ; 

__attribute__((used)) static void
nv50_mstm_hotplug(struct drm_dp_mst_topology_mgr *mgr)
{
	struct nv50_mstm *mstm = nv50_mstm(mgr);
	drm_kms_helper_hotplug_event(mstm->outp->base.base.dev);
}