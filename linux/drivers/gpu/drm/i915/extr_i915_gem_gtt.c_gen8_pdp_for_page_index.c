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
typedef  int /*<<< orphan*/  u64 ;
struct i915_ppgtt {struct i915_page_directory* pd; } ;
struct i915_page_directory {int dummy; } ;
struct i915_address_space {int top; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen8_pd_index (int /*<<< orphan*/  const,int) ; 
 struct i915_page_directory* i915_pd_entry (struct i915_page_directory*,int /*<<< orphan*/ ) ; 
 struct i915_ppgtt* i915_vm_to_ppgtt (struct i915_address_space* const) ; 

__attribute__((used)) static inline struct i915_page_directory *
gen8_pdp_for_page_index(struct i915_address_space * const vm, const u64 idx)
{
	struct i915_ppgtt * const ppgtt = i915_vm_to_ppgtt(vm);

	if (vm->top == 2)
		return ppgtt->pd;
	else
		return i915_pd_entry(ppgtt->pd, gen8_pd_index(idx, vm->top));
}