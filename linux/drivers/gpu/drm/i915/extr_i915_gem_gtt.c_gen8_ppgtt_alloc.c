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
typedef  int u64 ;
struct i915_address_space {int /*<<< orphan*/  top; int /*<<< orphan*/  total; } ;
struct TYPE_2__ {int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GEN8_PTE_SHIFT ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int /*<<< orphan*/ ) ; 
 int __gen8_ppgtt_alloc (struct i915_address_space*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gen8_ppgtt_clear (struct i915_address_space*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* i915_vm_to_ppgtt (struct i915_address_space*) ; 
 int range_overflows (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gen8_ppgtt_alloc(struct i915_address_space *vm,
			    u64 start, u64 length)
{
	u64 from;
	int err;

	GEM_BUG_ON(!IS_ALIGNED(start, BIT_ULL(GEN8_PTE_SHIFT)));
	GEM_BUG_ON(!IS_ALIGNED(length, BIT_ULL(GEN8_PTE_SHIFT)));
	GEM_BUG_ON(range_overflows(start, length, vm->total));

	start >>= GEN8_PTE_SHIFT;
	length >>= GEN8_PTE_SHIFT;
	GEM_BUG_ON(length == 0);
	from = start;

	err = __gen8_ppgtt_alloc(vm, i915_vm_to_ppgtt(vm)->pd,
				 &start, start + length, vm->top);
	if (unlikely(err && from != start))
		__gen8_ppgtt_clear(vm, i915_vm_to_ppgtt(vm)->pd,
				   from, start, vm->top);

	return err;
}