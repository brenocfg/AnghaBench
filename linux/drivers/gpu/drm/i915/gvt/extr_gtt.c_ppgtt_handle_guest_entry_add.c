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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct intel_vgpu_ppgtt_spt {TYPE_1__ shadow_page; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  id; } ;
struct intel_gvt_gtt_entry {int /*<<< orphan*/  type; int /*<<< orphan*/  val64; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct intel_vgpu_ppgtt_spt*) ; 
 int PTR_ERR (struct intel_vgpu_ppgtt_spt*) ; 
 int /*<<< orphan*/  get_next_pt_type (int /*<<< orphan*/ ) ; 
 scalar_t__ gtt_type_is_pt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vdbg_mm (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppgtt_generate_shadow_entry (struct intel_gvt_gtt_entry*,struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  ppgtt_get_shadow_entry (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int ppgtt_populate_shadow_entry (struct intel_vgpu*,struct intel_vgpu_ppgtt_spt*,unsigned long,struct intel_gvt_gtt_entry*) ; 
 struct intel_vgpu_ppgtt_spt* ppgtt_populate_spt_by_guest_entry (struct intel_vgpu*,struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  ppgtt_set_shadow_entry (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  trace_spt_guest_change (int /*<<< orphan*/ ,char*,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ppgtt_handle_guest_entry_add(struct intel_vgpu_ppgtt_spt *spt,
		struct intel_gvt_gtt_entry *we, unsigned long index)
{
	struct intel_vgpu *vgpu = spt->vgpu;
	struct intel_gvt_gtt_entry m;
	struct intel_vgpu_ppgtt_spt *s;
	int ret;

	trace_spt_guest_change(spt->vgpu->id, "add", spt, spt->shadow_page.type,
			       we->val64, index);

	gvt_vdbg_mm("add shadow entry: type %d, index %lu, value %llx\n",
		    we->type, index, we->val64);

	if (gtt_type_is_pt(get_next_pt_type(we->type))) {
		s = ppgtt_populate_spt_by_guest_entry(vgpu, we);
		if (IS_ERR(s)) {
			ret = PTR_ERR(s);
			goto fail;
		}
		ppgtt_get_shadow_entry(spt, &m, index);
		ppgtt_generate_shadow_entry(&m, s, we);
		ppgtt_set_shadow_entry(spt, &m, index);
	} else {
		ret = ppgtt_populate_shadow_entry(vgpu, spt, index, we);
		if (ret)
			goto fail;
	}
	return 0;
fail:
	gvt_vgpu_err("fail: spt %p guest entry 0x%llx type %d\n",
		spt, we->val64, we->type);
	return ret;
}