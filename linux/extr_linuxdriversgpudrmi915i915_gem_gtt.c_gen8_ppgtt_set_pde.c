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
struct i915_page_table {int dummy; } ;
struct i915_page_directory {struct i915_page_table** page_table; } ;
struct i915_address_space {int dummy; } ;
typedef  int /*<<< orphan*/  gen8_pde_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  gen8_pde_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic_px (struct i915_page_directory*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_dma (struct i915_page_table*) ; 

__attribute__((used)) static void gen8_ppgtt_set_pde(struct i915_address_space *vm,
			       struct i915_page_directory *pd,
			       struct i915_page_table *pt,
			       unsigned int pde)
{
	gen8_pde_t *vaddr;

	pd->page_table[pde] = pt;

	vaddr = kmap_atomic_px(pd);
	vaddr[pde] = gen8_pde_encode(px_dma(pt), I915_CACHE_LLC);
	kunmap_atomic(vaddr);
}