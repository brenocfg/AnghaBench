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
struct i915_pml4 {struct i915_page_directory_pointer** pdps; } ;
struct i915_page_directory_pointer {int dummy; } ;
typedef  int /*<<< orphan*/  gen8_ppgtt_pml4e_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  gen8_pml4e_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic_px (struct i915_pml4*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_dma (struct i915_page_directory_pointer*) ; 

__attribute__((used)) static void gen8_ppgtt_set_pml4e(struct i915_pml4 *pml4,
				 struct i915_page_directory_pointer *pdp,
				 unsigned int pml4e)
{
	gen8_ppgtt_pml4e_t *vaddr;

	pml4->pdps[pml4e] = pdp;

	vaddr = kmap_atomic_px(pml4);
	vaddr[pml4e] = gen8_pml4e_encode(px_dma(pdp), I915_CACHE_LLC);
	kunmap_atomic(vaddr);
}