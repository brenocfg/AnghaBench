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
struct i915_page_table {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;
struct i915_address_space {TYPE_1__ scratch_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  fill_px (struct i915_address_space*,struct i915_page_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_pte_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_initialize_pt(struct i915_address_space *vm,
			       struct i915_page_table *pt)
{
	fill_px(vm, pt,
		gen8_pte_encode(vm->scratch_page.daddr, I915_CACHE_LLC, 0));
}