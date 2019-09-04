#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_vgpu_workload {struct intel_vgpu* vgpu; int /*<<< orphan*/  status; int /*<<< orphan*/  shadow_ctx_active; int /*<<< orphan*/  shadow_ctx_status_wq; int /*<<< orphan*/  shadow_bb; int /*<<< orphan*/  list; } ;
struct intel_vgpu_submission {int /*<<< orphan*/  workloads; } ;
struct intel_vgpu {struct intel_vgpu_submission submission; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct intel_vgpu_workload* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct intel_vgpu_workload* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_vgpu_workload *
alloc_workload(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_submission *s = &vgpu->submission;
	struct intel_vgpu_workload *workload;

	workload = kmem_cache_zalloc(s->workloads, GFP_KERNEL);
	if (!workload)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&workload->list);
	INIT_LIST_HEAD(&workload->shadow_bb);

	init_waitqueue_head(&workload->shadow_ctx_status_wq);
	atomic_set(&workload->shadow_ctx_active, 0);

	workload->status = -EINPROGRESS;
	workload->vgpu = vgpu;

	return workload;
}