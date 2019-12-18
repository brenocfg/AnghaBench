#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct parser_exec_state {scalar_t__ buf_addr_type; scalar_t__ buf_type; unsigned long ip_gma; TYPE_5__* ip_va; TYPE_5__* rb_va; int /*<<< orphan*/  is_ctx_wa; TYPE_4__* workload; struct intel_vgpu* vgpu; } ;
struct intel_vgpu_shadow_bb {int ppgtt; int clflush; int accessing; TYPE_5__* obj; TYPE_5__* va; TYPE_5__* bb_offset; TYPE_5__* bb_start_cmd_va; int /*<<< orphan*/  list; } ;
struct intel_vgpu_mm {int dummy; } ;
struct TYPE_17__ {struct intel_vgpu_mm* ggtt_mm; } ;
struct intel_vgpu {TYPE_2__* gvt; TYPE_1__ gtt; } ;
struct TYPE_19__ {int /*<<< orphan*/  size; } ;
struct TYPE_21__ {TYPE_3__ base; } ;
struct TYPE_20__ {int /*<<< orphan*/  shadow_bb; struct intel_vgpu_mm* shadow_mm; } ;
struct TYPE_18__ {int /*<<< orphan*/  dev_priv; } ;

/* Variables and functions */
 scalar_t__ BATCH_BUFFER_INSTRUCTION ; 
 int CLFLUSH_BEFORE ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GTT_BUFFER ; 
 unsigned long I915_GTT_PAGE_MASK ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long INTEL_GVT_INVALID_ADDR ; 
 scalar_t__ IS_ERR (TYPE_5__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (TYPE_5__*) ; 
 int audit_bb_end (struct parser_exec_state*,TYPE_5__*) ; 
 int copy_gma_to_hva (struct intel_vgpu*,struct intel_vgpu_mm*,unsigned long,unsigned long,TYPE_5__*) ; 
 int /*<<< orphan*/  drm_clflush_virt_range (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int find_bb_size (struct parser_exec_state*,unsigned long*,unsigned long*) ; 
 unsigned long get_gma_bb_from_cmd (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 TYPE_5__* i915_gem_object_create_shmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_finish_access (TYPE_5__*) ; 
 TYPE_5__* i915_gem_object_pin_map (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_prepare_write (TYPE_5__*,int*) ; 
 int /*<<< orphan*/  i915_gem_object_put (TYPE_5__*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (TYPE_5__*) ; 
 int /*<<< orphan*/  kfree (struct intel_vgpu_shadow_bb*) ; 
 struct intel_vgpu_shadow_bb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round_up (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perform_bb_shadow(struct parser_exec_state *s)
{
	struct intel_vgpu *vgpu = s->vgpu;
	struct intel_vgpu_shadow_bb *bb;
	unsigned long gma = 0;
	unsigned long bb_size;
	unsigned long bb_end_cmd_offset;
	int ret = 0;
	struct intel_vgpu_mm *mm = (s->buf_addr_type == GTT_BUFFER) ?
		s->vgpu->gtt.ggtt_mm : s->workload->shadow_mm;
	unsigned long start_offset = 0;

	/* get the start gm address of the batch buffer */
	gma = get_gma_bb_from_cmd(s, 1);
	if (gma == INTEL_GVT_INVALID_ADDR)
		return -EFAULT;

	ret = find_bb_size(s, &bb_size, &bb_end_cmd_offset);
	if (ret)
		return ret;

	bb = kzalloc(sizeof(*bb), GFP_KERNEL);
	if (!bb)
		return -ENOMEM;

	bb->ppgtt = (s->buf_addr_type == GTT_BUFFER) ? false : true;

	/* the start_offset stores the batch buffer's start gma's
	 * offset relative to page boundary. so for non-privileged batch
	 * buffer, the shadowed gem object holds exactly the same page
	 * layout as original gem object. This is for the convience of
	 * replacing the whole non-privilged batch buffer page to this
	 * shadowed one in PPGTT at the same gma address. (this replacing
	 * action is not implemented yet now, but may be necessary in
	 * future).
	 * for prileged batch buffer, we just change start gma address to
	 * that of shadowed page.
	 */
	if (bb->ppgtt)
		start_offset = gma & ~I915_GTT_PAGE_MASK;

	bb->obj = i915_gem_object_create_shmem(s->vgpu->gvt->dev_priv,
					       round_up(bb_size + start_offset,
							PAGE_SIZE));
	if (IS_ERR(bb->obj)) {
		ret = PTR_ERR(bb->obj);
		goto err_free_bb;
	}

	ret = i915_gem_object_prepare_write(bb->obj, &bb->clflush);
	if (ret)
		goto err_free_obj;

	bb->va = i915_gem_object_pin_map(bb->obj, I915_MAP_WB);
	if (IS_ERR(bb->va)) {
		ret = PTR_ERR(bb->va);
		goto err_finish_shmem_access;
	}

	if (bb->clflush & CLFLUSH_BEFORE) {
		drm_clflush_virt_range(bb->va, bb->obj->base.size);
		bb->clflush &= ~CLFLUSH_BEFORE;
	}

	ret = copy_gma_to_hva(s->vgpu, mm,
			      gma, gma + bb_size,
			      bb->va + start_offset);
	if (ret < 0) {
		gvt_vgpu_err("fail to copy guest ring buffer\n");
		ret = -EFAULT;
		goto err_unmap;
	}

	ret = audit_bb_end(s, bb->va + start_offset + bb_end_cmd_offset);
	if (ret)
		goto err_unmap;

	INIT_LIST_HEAD(&bb->list);
	list_add(&bb->list, &s->workload->shadow_bb);

	bb->accessing = true;
	bb->bb_start_cmd_va = s->ip_va;

	if ((s->buf_type == BATCH_BUFFER_INSTRUCTION) && (!s->is_ctx_wa))
		bb->bb_offset = s->ip_va - s->rb_va;
	else
		bb->bb_offset = 0;

	/*
	 * ip_va saves the virtual address of the shadow batch buffer, while
	 * ip_gma saves the graphics address of the original batch buffer.
	 * As the shadow batch buffer is just a copy from the originial one,
	 * it should be right to use shadow batch buffer'va and original batch
	 * buffer's gma in pair. After all, we don't want to pin the shadow
	 * buffer here (too early).
	 */
	s->ip_va = bb->va + start_offset;
	s->ip_gma = gma;
	return 0;
err_unmap:
	i915_gem_object_unpin_map(bb->obj);
err_finish_shmem_access:
	i915_gem_object_finish_access(bb->obj);
err_free_obj:
	i915_gem_object_put(bb->obj);
err_free_bb:
	kfree(bb);
	return ret;
}