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
struct TYPE_2__ {int /*<<< orphan*/ * workload_q_head; } ;
struct intel_vgpu {int active; TYPE_1__ submission; int /*<<< orphan*/  vgpu_lock; struct intel_gvt* gvt; int /*<<< orphan*/  id; } ;
struct intel_gvt {int dummy; } ;
typedef  enum intel_engine_id { ____Placeholder_intel_engine_id } intel_engine_id ;

/* Variables and functions */
 int ENOMEM ; 
 struct intel_vgpu* ERR_PTR (int) ; 
 int I915_NUM_ENGINES ; 
 int /*<<< orphan*/  IDLE_VGPU_IDR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int intel_vgpu_init_sched_policy (struct intel_vgpu*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct intel_vgpu*) ; 
 struct intel_vgpu* vzalloc (int) ; 

struct intel_vgpu *intel_gvt_create_idle_vgpu(struct intel_gvt *gvt)
{
	struct intel_vgpu *vgpu;
	enum intel_engine_id i;
	int ret;

	vgpu = vzalloc(sizeof(*vgpu));
	if (!vgpu)
		return ERR_PTR(-ENOMEM);

	vgpu->id = IDLE_VGPU_IDR;
	vgpu->gvt = gvt;
	mutex_init(&vgpu->vgpu_lock);

	for (i = 0; i < I915_NUM_ENGINES; i++)
		INIT_LIST_HEAD(&vgpu->submission.workload_q_head[i]);

	ret = intel_vgpu_init_sched_policy(vgpu);
	if (ret)
		goto out_free_vgpu;

	vgpu->active = false;

	return vgpu;

out_free_vgpu:
	vfree(vgpu);
	return ERR_PTR(ret);
}