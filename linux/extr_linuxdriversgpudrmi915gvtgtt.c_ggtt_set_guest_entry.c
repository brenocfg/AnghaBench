#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  virtual_ggtt; } ;
struct intel_vgpu_mm {scalar_t__ type; TYPE_4__* vgpu; TYPE_3__ ggtt_mm; } ;
struct intel_gvt_gtt_pte_ops {int /*<<< orphan*/  (* set_entry ) (int /*<<< orphan*/ ,struct intel_gvt_gtt_entry*,unsigned long,int,int /*<<< orphan*/ ,TYPE_4__*) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_8__ {TYPE_2__* gvt; } ;
struct TYPE_5__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_6__ {TYPE_1__ gtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ INTEL_GVT_MM_GGTT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct intel_gvt_gtt_entry*,unsigned long,int,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void ggtt_set_guest_entry(struct intel_vgpu_mm *mm,
		struct intel_gvt_gtt_entry *entry, unsigned long index)
{
	struct intel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT);

	pte_ops->set_entry(mm->ggtt_mm.virtual_ggtt, entry, index,
			   false, 0, mm->vgpu);
}