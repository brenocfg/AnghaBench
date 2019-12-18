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
struct intel_gvt_gtt_entry {int type; int /*<<< orphan*/  val64; } ;

/* Variables and functions */
 int GTT_TYPE_PPGTT_PDE_ENTRY ; 
 int GTT_TYPE_PPGTT_PDP_ENTRY ; 
#define  GTT_TYPE_PPGTT_PTE_1G_ENTRY 129 
#define  GTT_TYPE_PPGTT_PTE_2M_ENTRY 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _PAGE_PSE ; 
 scalar_t__ gen8_gtt_test_pse (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static void gen8_gtt_clear_pse(struct intel_gvt_gtt_entry *e)
{
	if (gen8_gtt_test_pse(e)) {
		switch (e->type) {
		case GTT_TYPE_PPGTT_PTE_2M_ENTRY:
			e->val64 &= ~_PAGE_PSE;
			e->type = GTT_TYPE_PPGTT_PDE_ENTRY;
			break;
		case GTT_TYPE_PPGTT_PTE_1G_ENTRY:
			e->type = GTT_TYPE_PPGTT_PDP_ENTRY;
			e->val64 &= ~_PAGE_PSE;
			break;
		default:
			WARN_ON(1);
		}
	}
}