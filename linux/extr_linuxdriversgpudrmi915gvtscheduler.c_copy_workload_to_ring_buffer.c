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
typedef  int /*<<< orphan*/  u32 ;
struct intel_vgpu_workload {int rb_len; struct i915_request* req; int /*<<< orphan*/ * shadow_ring_buffer_va; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int dummy; } ;
struct i915_request {int /*<<< orphan*/  hw_context; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 scalar_t__ IS_BROXTON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_KABYLAKE (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int /*<<< orphan*/  intel_vgpu_restore_inhibit_context (struct intel_vgpu*,struct i915_request*) ; 
 scalar_t__ is_inhibit_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int copy_workload_to_ring_buffer(struct intel_vgpu_workload *workload)
{
	struct intel_vgpu *vgpu = workload->vgpu;
	struct i915_request *req = workload->req;
	void *shadow_ring_buffer_va;
	u32 *cs;

	if ((IS_KABYLAKE(req->i915) || IS_BROXTON(req->i915))
		&& is_inhibit_context(req->hw_context))
		intel_vgpu_restore_inhibit_context(vgpu, req);

	/* allocate shadow ring buffer */
	cs = intel_ring_begin(workload->req, workload->rb_len / sizeof(u32));
	if (IS_ERR(cs)) {
		gvt_vgpu_err("fail to alloc size =%ld shadow  ring buffer\n",
			workload->rb_len);
		return PTR_ERR(cs);
	}

	shadow_ring_buffer_va = workload->shadow_ring_buffer_va;

	/* get shadow ring buffer va */
	workload->shadow_ring_buffer_va = cs;

	memcpy(cs, shadow_ring_buffer_va,
			workload->rb_len);

	cs += workload->rb_len / sizeof(u32);
	intel_ring_advance(workload->req, cs);

	return 0;
}