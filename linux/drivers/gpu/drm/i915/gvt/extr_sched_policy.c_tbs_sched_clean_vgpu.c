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
struct intel_vgpu {int /*<<< orphan*/ * sched_data; struct intel_gvt* gvt; } ;
struct TYPE_2__ {struct gvt_sched_data* sched_data; } ;
struct intel_gvt {int /*<<< orphan*/  vgpu_idr; TYPE_1__ scheduler; } ;
struct gvt_sched_data {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tbs_sched_clean_vgpu(struct intel_vgpu *vgpu)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct gvt_sched_data *sched_data = gvt->scheduler.sched_data;

	kfree(vgpu->sched_data);
	vgpu->sched_data = NULL;

	/* this vgpu id has been removed */
	if (idr_is_empty(&gvt->vgpu_idr))
		hrtimer_cancel(&sched_data->timer);
}