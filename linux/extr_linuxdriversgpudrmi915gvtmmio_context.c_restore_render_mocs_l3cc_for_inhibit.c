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
typedef  int /*<<< orphan*/  u32 ;
struct intel_vgpu {int /*<<< orphan*/  id; } ;
struct i915_request {TYPE_1__* engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN9_LNCFCMOCS (unsigned int) ; 
 int GEN9_MOCS_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int /*<<< orphan*/  vgpu_vreg_t (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
restore_render_mocs_l3cc_for_inhibit(struct intel_vgpu *vgpu,
				     struct i915_request *req)
{
	unsigned int index;
	u32 *cs;

	cs = intel_ring_begin(req, 2 * GEN9_MOCS_SIZE / 2 + 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(GEN9_MOCS_SIZE / 2);

	for (index = 0; index < GEN9_MOCS_SIZE / 2; index++) {
		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(index));
		*cs++ = vgpu_vreg_t(vgpu, GEN9_LNCFCMOCS(index));
		gvt_dbg_core("add lri reg pair 0x%x:0x%x in inhibit ctx, vgpu:%d, rind_id:%d\n",
			      *(cs-2), *(cs-1), vgpu->id, req->engine->id);

	}

	*cs++ = MI_NOOP;
	intel_ring_advance(req, cs);

	return 0;
}