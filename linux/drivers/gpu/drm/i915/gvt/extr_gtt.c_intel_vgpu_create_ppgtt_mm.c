#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int root_entry_type; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  list; int /*<<< orphan*/ * guest_pdps; } ;
struct intel_vgpu_mm {TYPE_2__ ppgtt_mm; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  ppgtt_mm_list_head; } ;
struct intel_vgpu {TYPE_1__ gtt; struct intel_gvt* gvt; } ;
struct TYPE_6__ {int /*<<< orphan*/  ppgtt_mm_lock; int /*<<< orphan*/  ppgtt_mm_lru_list_head; } ;
struct intel_gvt {TYPE_3__ gtt; } ;
typedef  enum intel_gvt_gtt_type { ____Placeholder_intel_gvt_gtt_type } intel_gvt_gtt_type ;

/* Variables and functions */
 int ENOMEM ; 
 struct intel_vgpu_mm* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GTT_TYPE_PPGTT_ROOT_L3_ENTRY ; 
 int GTT_TYPE_PPGTT_ROOT_L4_ENTRY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTEL_GVT_MM_PPGTT ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int shadow_ppgtt_mm (struct intel_vgpu_mm*) ; 
 struct intel_vgpu_mm* vgpu_alloc_mm (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_free_mm (struct intel_vgpu_mm*) ; 

struct intel_vgpu_mm *intel_vgpu_create_ppgtt_mm(struct intel_vgpu *vgpu,
		enum intel_gvt_gtt_type root_entry_type, u64 pdps[])
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct intel_vgpu_mm *mm;
	int ret;

	mm = vgpu_alloc_mm(vgpu);
	if (!mm)
		return ERR_PTR(-ENOMEM);

	mm->type = INTEL_GVT_MM_PPGTT;

	GEM_BUG_ON(root_entry_type != GTT_TYPE_PPGTT_ROOT_L3_ENTRY &&
		   root_entry_type != GTT_TYPE_PPGTT_ROOT_L4_ENTRY);
	mm->ppgtt_mm.root_entry_type = root_entry_type;

	INIT_LIST_HEAD(&mm->ppgtt_mm.list);
	INIT_LIST_HEAD(&mm->ppgtt_mm.lru_list);

	if (root_entry_type == GTT_TYPE_PPGTT_ROOT_L4_ENTRY)
		mm->ppgtt_mm.guest_pdps[0] = pdps[0];
	else
		memcpy(mm->ppgtt_mm.guest_pdps, pdps,
		       sizeof(mm->ppgtt_mm.guest_pdps));

	ret = shadow_ppgtt_mm(mm);
	if (ret) {
		gvt_vgpu_err("failed to shadow ppgtt mm\n");
		vgpu_free_mm(mm);
		return ERR_PTR(ret);
	}

	list_add_tail(&mm->ppgtt_mm.list, &vgpu->gtt.ppgtt_mm_list_head);

	mutex_lock(&gvt->gtt.ppgtt_mm_lock);
	list_add_tail(&mm->ppgtt_mm.lru_list, &gvt->gtt.ppgtt_mm_lru_list_head);
	mutex_unlock(&gvt->gtt.ppgtt_mm_lock);

	return mm;
}