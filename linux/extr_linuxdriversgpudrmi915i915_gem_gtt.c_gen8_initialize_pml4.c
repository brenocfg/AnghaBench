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
struct i915_pml4 {scalar_t__ pdps; } ;
struct i915_address_space {int /*<<< orphan*/  scratch_pdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_PML4ES_PER_PML4 ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  fill_px (struct i915_address_space*,struct i915_pml4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_pml4e_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_p (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_initialize_pml4(struct i915_address_space *vm,
				 struct i915_pml4 *pml4)
{
	fill_px(vm, pml4,
		gen8_pml4e_encode(px_dma(vm->scratch_pdp), I915_CACHE_LLC));
	memset_p((void **)pml4->pdps, vm->scratch_pdp, GEN8_PML4ES_PER_PML4);
}