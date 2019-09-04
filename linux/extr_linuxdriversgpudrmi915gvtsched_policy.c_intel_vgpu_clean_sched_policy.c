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
struct intel_vgpu {TYPE_3__* gvt; } ;
struct TYPE_5__ {TYPE_1__* sched_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  sched_lock; TYPE_2__ scheduler; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clean_vgpu ) (struct intel_vgpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*) ; 

void intel_vgpu_clean_sched_policy(struct intel_vgpu *vgpu)
{
	mutex_lock(&vgpu->gvt->sched_lock);
	vgpu->gvt->scheduler.sched_ops->clean_vgpu(vgpu);
	mutex_unlock(&vgpu->gvt->sched_lock);
}