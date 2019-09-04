#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct list_head {int dummy; } ;
struct TYPE_21__ {int guest_gma; int valid; } ;
struct TYPE_20__ {int guest_gma; int size; } ;
struct TYPE_22__ {TYPE_4__ per_ctx; TYPE_3__ indirect_ctx; } ;
struct execlist_ctx_descriptor_format {int lrca; } ;
struct intel_vgpu_workload {int rb_tail; int ring_id; int rb_head; int rb_start; int rb_ctl; TYPE_5__ wa_ctx; scalar_t__ ring_context_gpa; struct execlist_ctx_descriptor_format ctx_desc; } ;
struct intel_vgpu_submission {int /*<<< orphan*/  workloads; } ;
struct TYPE_19__ {int /*<<< orphan*/  ggtt_mm; } ;
struct intel_vgpu {TYPE_2__ gtt; TYPE_1__* gvt; struct intel_vgpu_submission submission; } ;
struct TYPE_23__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_6__ drm; } ;
struct TYPE_26__ {int /*<<< orphan*/  val; } ;
struct TYPE_25__ {int /*<<< orphan*/  val; } ;
struct TYPE_24__ {int /*<<< orphan*/  val; } ;
struct TYPE_18__ {struct drm_i915_private* dev_priv; } ;
struct TYPE_17__ {int /*<<< orphan*/  val; } ;
struct TYPE_16__ {int /*<<< orphan*/  val; } ;
struct TYPE_15__ {int /*<<< orphan*/  val; } ;
struct TYPE_14__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int CACHELINE_BYTES ; 
 int EINVAL ; 
 struct intel_vgpu_workload* ERR_PTR (int) ; 
 int /*<<< orphan*/  GVT_FAILSAFE_GUEST_ERR ; 
 int I915_GTT_PAGE_SHIFT ; 
 int INDIRECT_CTX_ADDR_MASK ; 
 int INDIRECT_CTX_SIZE_MASK ; 
 scalar_t__ INTEL_GVT_INVALID_ADDR ; 
 scalar_t__ IS_ERR (struct intel_vgpu_workload*) ; 
 int PER_CTX_ADDR_MASK ; 
 int RB_HEAD_OFF_MASK ; 
 int RB_TAIL_OFF_MASK ; 
 int RCS ; 
 scalar_t__ RING_CTX_OFF (int /*<<< orphan*/ ) ; 
 struct intel_vgpu_workload* alloc_workload (struct intel_vgpu*) ; 
 TYPE_13__ bb_per_ctx_ptr ; 
 TYPE_12__ ctx_ctrl ; 
 int /*<<< orphan*/  enter_failsafe_mode (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 struct intel_vgpu_workload* get_last_workload (struct list_head*) ; 
 int /*<<< orphan*/  gvt_dbg_el (char*,...) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int) ; 
 int /*<<< orphan*/  intel_gvt_hypervisor_read_gpa (struct intel_vgpu*,scalar_t__,int*,int) ; 
 int intel_gvt_scan_and_shadow_workload (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_vgpu_destroy_workload (struct intel_vgpu_workload*) ; 
 scalar_t__ intel_vgpu_gma_to_gpa (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct intel_vgpu_workload*) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int prepare_mm (struct intel_vgpu_workload*) ; 
 TYPE_11__ rb_ctrl ; 
 TYPE_10__ rb_start ; 
 TYPE_9__ rcs_indirect_ctx ; 
 TYPE_8__ ring_header ; 
 TYPE_7__ ring_tail ; 
 scalar_t__ same_context (struct execlist_ctx_descriptor_format*,struct execlist_ctx_descriptor_format*) ; 
 scalar_t__ vgpu_is_vm_unhealthy (int) ; 
 struct list_head* workload_q_head (struct intel_vgpu*,int) ; 

struct intel_vgpu_workload *
intel_vgpu_create_workload(struct intel_vgpu *vgpu, int ring_id,
			   struct execlist_ctx_descriptor_format *desc)
{
	struct intel_vgpu_submission *s = &vgpu->submission;
	struct list_head *q = workload_q_head(vgpu, ring_id);
	struct intel_vgpu_workload *last_workload = get_last_workload(q);
	struct intel_vgpu_workload *workload = NULL;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	u64 ring_context_gpa;
	u32 head, tail, start, ctl, ctx_ctl, per_ctx, indirect_ctx;
	int ret;

	ring_context_gpa = intel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm,
			(u32)((desc->lrca + 1) << I915_GTT_PAGE_SHIFT));
	if (ring_context_gpa == INTEL_GVT_INVALID_ADDR) {
		gvt_vgpu_err("invalid guest context LRCA: %x\n", desc->lrca);
		return ERR_PTR(-EINVAL);
	}

	intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(ring_header.val), &head, 4);

	intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(ring_tail.val), &tail, 4);

	head &= RB_HEAD_OFF_MASK;
	tail &= RB_TAIL_OFF_MASK;

	if (last_workload && same_context(&last_workload->ctx_desc, desc)) {
		gvt_dbg_el("ring id %d cur workload == last\n", ring_id);
		gvt_dbg_el("ctx head %x real head %lx\n", head,
				last_workload->rb_tail);
		/*
		 * cannot use guest context head pointer here,
		 * as it might not be updated at this time
		 */
		head = last_workload->rb_tail;
	}

	gvt_dbg_el("ring id %d begin a new workload\n", ring_id);

	/* record some ring buffer register values for scan and shadow */
	intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(rb_start.val), &start, 4);
	intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(rb_ctrl.val), &ctl, 4);
	intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(ctx_ctrl.val), &ctx_ctl, 4);

	workload = alloc_workload(vgpu);
	if (IS_ERR(workload))
		return workload;

	workload->ring_id = ring_id;
	workload->ctx_desc = *desc;
	workload->ring_context_gpa = ring_context_gpa;
	workload->rb_head = head;
	workload->rb_tail = tail;
	workload->rb_start = start;
	workload->rb_ctl = ctl;

	if (ring_id == RCS) {
		intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(bb_per_ctx_ptr.val), &per_ctx, 4);
		intel_gvt_hypervisor_read_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(rcs_indirect_ctx.val), &indirect_ctx, 4);

		workload->wa_ctx.indirect_ctx.guest_gma =
			indirect_ctx & INDIRECT_CTX_ADDR_MASK;
		workload->wa_ctx.indirect_ctx.size =
			(indirect_ctx & INDIRECT_CTX_SIZE_MASK) *
			CACHELINE_BYTES;
		workload->wa_ctx.per_ctx.guest_gma =
			per_ctx & PER_CTX_ADDR_MASK;
		workload->wa_ctx.per_ctx.valid = per_ctx & 1;
	}

	gvt_dbg_el("workload %p ring id %d head %x tail %x start %x ctl %x\n",
			workload, ring_id, head, tail, start, ctl);

	ret = prepare_mm(workload);
	if (ret) {
		kmem_cache_free(s->workloads, workload);
		return ERR_PTR(ret);
	}

	/* Only scan and shadow the first workload in the queue
	 * as there is only one pre-allocated buf-obj for shadow.
	 */
	if (list_empty(workload_q_head(vgpu, ring_id))) {
		intel_runtime_pm_get(dev_priv);
		mutex_lock(&dev_priv->drm.struct_mutex);
		ret = intel_gvt_scan_and_shadow_workload(workload);
		mutex_unlock(&dev_priv->drm.struct_mutex);
		intel_runtime_pm_put(dev_priv);
	}

	if (ret) {
		if (vgpu_is_vm_unhealthy(ret))
			enter_failsafe_mode(vgpu, GVT_FAILSAFE_GUEST_ERR);
		intel_vgpu_destroy_workload(workload);
		return ERR_PTR(ret);
	}

	return workload;
}