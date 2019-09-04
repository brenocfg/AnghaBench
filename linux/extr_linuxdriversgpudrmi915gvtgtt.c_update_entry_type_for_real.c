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
struct intel_gvt_gtt_pte_ops {int /*<<< orphan*/  (* test_pse ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GTT_TYPE_INVALID ; 
#define  GTT_TYPE_PPGTT_PDE_ENTRY 130 
#define  GTT_TYPE_PPGTT_PDP_ENTRY 129 
#define  GTT_TYPE_PPGTT_PTE_4K_ENTRY 128 
 void* get_pse_type (int) ; 
 int /*<<< orphan*/  gtt_type_is_entry (int) ; 
 int /*<<< orphan*/  stub1 (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static void update_entry_type_for_real(struct intel_gvt_gtt_pte_ops *pte_ops,
	struct intel_gvt_gtt_entry *entry, bool ips)
{
	switch (entry->type) {
	case GTT_TYPE_PPGTT_PDE_ENTRY:
	case GTT_TYPE_PPGTT_PDP_ENTRY:
		if (pte_ops->test_pse(entry))
			entry->type = get_pse_type(entry->type);
		break;
	case GTT_TYPE_PPGTT_PTE_4K_ENTRY:
		if (ips)
			entry->type = get_pse_type(entry->type);
		break;
	default:
		GEM_BUG_ON(!gtt_type_is_entry(entry->type));
	}

	GEM_BUG_ON(entry->type == GTT_TYPE_INVALID);
}