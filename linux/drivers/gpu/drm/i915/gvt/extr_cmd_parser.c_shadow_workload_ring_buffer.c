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
struct intel_vgpu_workload {int ring_id; unsigned long rb_len; unsigned long rb_tail; unsigned long rb_head; unsigned long rb_start; void* shadow_ring_buffer_va; int /*<<< orphan*/  rb_ctl; struct intel_vgpu* vgpu; } ;
struct intel_vgpu_submission {unsigned long* ring_scan_buffer_size; void** ring_scan_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  ggtt_mm; } ;
struct intel_vgpu {TYPE_1__ gtt; struct intel_vgpu_submission submission; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long _RING_CTL_BUF_SIZE (int /*<<< orphan*/ ) ; 
 int copy_gma_to_hva (struct intel_vgpu*,int /*<<< orphan*/ ,unsigned long,unsigned long,void*) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 void* krealloc (void*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shadow_workload_ring_buffer(struct intel_vgpu_workload *workload)
{
	struct intel_vgpu *vgpu = workload->vgpu;
	struct intel_vgpu_submission *s = &vgpu->submission;
	unsigned long gma_head, gma_tail, gma_top, guest_rb_size;
	void *shadow_ring_buffer_va;
	int ring_id = workload->ring_id;
	int ret;

	guest_rb_size = _RING_CTL_BUF_SIZE(workload->rb_ctl);

	/* calculate workload ring buffer size */
	workload->rb_len = (workload->rb_tail + guest_rb_size -
			workload->rb_head) % guest_rb_size;

	gma_head = workload->rb_start + workload->rb_head;
	gma_tail = workload->rb_start + workload->rb_tail;
	gma_top = workload->rb_start + guest_rb_size;

	if (workload->rb_len > s->ring_scan_buffer_size[ring_id]) {
		void *p;

		/* realloc the new ring buffer if needed */
		p = krealloc(s->ring_scan_buffer[ring_id], workload->rb_len,
				GFP_KERNEL);
		if (!p) {
			gvt_vgpu_err("fail to re-alloc ring scan buffer\n");
			return -ENOMEM;
		}
		s->ring_scan_buffer[ring_id] = p;
		s->ring_scan_buffer_size[ring_id] = workload->rb_len;
	}

	shadow_ring_buffer_va = s->ring_scan_buffer[ring_id];

	/* get shadow ring buffer va */
	workload->shadow_ring_buffer_va = shadow_ring_buffer_va;

	/* head > tail --> copy head <-> top */
	if (gma_head > gma_tail) {
		ret = copy_gma_to_hva(vgpu, vgpu->gtt.ggtt_mm,
				      gma_head, gma_top, shadow_ring_buffer_va);
		if (ret < 0) {
			gvt_vgpu_err("fail to copy guest ring buffer\n");
			return ret;
		}
		shadow_ring_buffer_va += ret;
		gma_head = workload->rb_start;
	}

	/* copy head or start <-> tail */
	ret = copy_gma_to_hva(vgpu, vgpu->gtt.ggtt_mm, gma_head, gma_tail,
				shadow_ring_buffer_va);
	if (ret < 0) {
		gvt_vgpu_err("fail to copy guest ring buffer\n");
		return ret;
	}
	return 0;
}