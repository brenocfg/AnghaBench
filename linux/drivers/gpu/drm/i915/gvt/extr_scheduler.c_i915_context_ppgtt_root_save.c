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
struct intel_vgpu_submission {void** i915_context_pdps; void* i915_context_pml4; } ;
struct i915_ppgtt {struct i915_page_directory* const pd; int /*<<< orphan*/  vm; } ;
struct i915_page_directory {int dummy; } ;

/* Variables and functions */
 int GEN8_3LVL_PDPES ; 
 struct i915_page_directory* i915_pd_entry (struct i915_page_directory* const,int) ; 
 scalar_t__ i915_vm_is_4lvl (int /*<<< orphan*/ *) ; 
 void* px_dma (struct i915_page_directory* const) ; 

__attribute__((used)) static void
i915_context_ppgtt_root_save(struct intel_vgpu_submission *s,
			     struct i915_ppgtt *ppgtt)
{
	int i;

	if (i915_vm_is_4lvl(&ppgtt->vm)) {
		s->i915_context_pml4 = px_dma(ppgtt->pd);
	} else {
		for (i = 0; i < GEN8_3LVL_PDPES; i++) {
			struct i915_page_directory * const pd =
				i915_pd_entry(ppgtt->pd, i);

			s->i915_context_pdps[i] = px_dma(pd);
		}
	}
}