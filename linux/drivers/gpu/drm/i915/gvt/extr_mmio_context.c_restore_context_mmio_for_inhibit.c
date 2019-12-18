#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_vgpu {int /*<<< orphan*/  id; struct intel_gvt* gvt; } ;
struct TYPE_3__ {int* ctx_mmio_count; struct engine_mmio* mmio; } ;
struct intel_gvt {TYPE_1__ engine_mmio_list; } ;
struct i915_request {TYPE_2__* engine; } ;
struct engine_mmio {int ring_id; int mask; int /*<<< orphan*/  reg; int /*<<< orphan*/  in_context; } ;
struct TYPE_4__ {int id; int (* emit_flush ) (struct i915_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_BARRIER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_mmio_reg_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int vgpu_vreg_t (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
restore_context_mmio_for_inhibit(struct intel_vgpu *vgpu,
				 struct i915_request *req)
{
	u32 *cs;
	int ret;
	struct engine_mmio *mmio;
	struct intel_gvt *gvt = vgpu->gvt;
	int ring_id = req->engine->id;
	int count = gvt->engine_mmio_list.ctx_mmio_count[ring_id];

	if (count == 0)
		return 0;

	ret = req->engine->emit_flush(req, EMIT_BARRIER);
	if (ret)
		return ret;

	cs = intel_ring_begin(req, count * 2 + 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(count);
	for (mmio = gvt->engine_mmio_list.mmio;
	     i915_mmio_reg_valid(mmio->reg); mmio++) {
		if (mmio->ring_id != ring_id ||
		    !mmio->in_context)
			continue;

		*cs++ = i915_mmio_reg_offset(mmio->reg);
		*cs++ = vgpu_vreg_t(vgpu, mmio->reg) |
				(mmio->mask << 16);
		gvt_dbg_core("add lri reg pair 0x%x:0x%x in inhibit ctx, vgpu:%d, rind_id:%d\n",
			      *(cs-2), *(cs-1), vgpu->id, ring_id);
	}

	*cs++ = MI_NOOP;
	intel_ring_advance(req, cs);

	ret = req->engine->emit_flush(req, EMIT_BARRIER);
	if (ret)
		return ret;

	return 0;
}