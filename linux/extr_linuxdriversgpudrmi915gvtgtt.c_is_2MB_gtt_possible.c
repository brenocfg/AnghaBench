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
struct intel_vgpu {TYPE_2__* gvt; } ;
struct intel_gvt_gtt_pte_ops {int /*<<< orphan*/  (* get_pfn ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_3__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_priv; TYPE_1__ gtt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HAS_PAGE_SIZES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_2M ; 
 unsigned long INTEL_GVT_INVALID_ADDR ; 
 int PageTransHuge (int /*<<< orphan*/ ) ; 
 unsigned long intel_gvt_hypervisor_gfn_to_mfn (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static int is_2MB_gtt_possible(struct intel_vgpu *vgpu,
	struct intel_gvt_gtt_entry *entry)
{
	struct intel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	unsigned long pfn;

	if (!HAS_PAGE_SIZES(vgpu->gvt->dev_priv, I915_GTT_PAGE_SIZE_2M))
		return 0;

	pfn = intel_gvt_hypervisor_gfn_to_mfn(vgpu, ops->get_pfn(entry));
	if (pfn == INTEL_GVT_INVALID_ADDR)
		return -EINVAL;

	return PageTransHuge(pfn_to_page(pfn));
}