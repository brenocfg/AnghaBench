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
struct vgpu_sched_data {int /*<<< orphan*/  active; } ;
struct intel_vgpu {TYPE_3__* gvt; int /*<<< orphan*/  id; struct vgpu_sched_data* sched_data; } ;
struct TYPE_5__ {TYPE_1__* sched_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  sched_lock; TYPE_2__ scheduler; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start_schedule ) (struct intel_vgpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*) ; 

void intel_vgpu_start_schedule(struct intel_vgpu *vgpu)
{
	struct vgpu_sched_data *vgpu_data = vgpu->sched_data;

	mutex_lock(&vgpu->gvt->sched_lock);
	if (!vgpu_data->active) {
		gvt_dbg_core("vgpu%d: start schedule\n", vgpu->id);
		vgpu->gvt->scheduler.sched_ops->start_schedule(vgpu);
	}
	mutex_unlock(&vgpu->gvt->sched_lock);
}