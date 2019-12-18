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
typedef  int u64 ;
struct i915_page_directory {int dummy; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int const GEN8_PTE_SHIFT ; 
 struct i915_page_directory* gen8_pdp_for_page_index (struct i915_address_space* const,int const) ; 

__attribute__((used)) static inline struct i915_page_directory *
gen8_pdp_for_page_address(struct i915_address_space * const vm, const u64 addr)
{
	return gen8_pdp_for_page_index(vm, addr >> GEN8_PTE_SHIFT);
}