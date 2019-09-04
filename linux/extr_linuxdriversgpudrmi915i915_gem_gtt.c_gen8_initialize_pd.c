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
struct i915_page_directory {scalar_t__ page_table; } ;
struct i915_address_space {int /*<<< orphan*/  scratch_pt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  I915_PDES ; 
 int /*<<< orphan*/  fill_px (struct i915_address_space*,struct i915_page_directory*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_pde_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_p (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_initialize_pd(struct i915_address_space *vm,
			       struct i915_page_directory *pd)
{
	fill_px(vm, pd,
		gen8_pde_encode(px_dma(vm->scratch_pt), I915_CACHE_LLC));
	memset_p((void **)pd->page_table, vm->scratch_pt, I915_PDES);
}