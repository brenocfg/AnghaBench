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
struct i915_page_directory_pointer {struct i915_page_directory** page_directory; } ;
struct i915_page_directory {int dummy; } ;
struct i915_address_space {int dummy; } ;
typedef  int /*<<< orphan*/  gen8_ppgtt_pdpe_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  gen8_pdpe_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic_px (struct i915_page_directory_pointer*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_dma (struct i915_page_directory*) ; 
 int /*<<< orphan*/  use_4lvl (struct i915_address_space*) ; 

__attribute__((used)) static void gen8_ppgtt_set_pdpe(struct i915_address_space *vm,
				struct i915_page_directory_pointer *pdp,
				struct i915_page_directory *pd,
				unsigned int pdpe)
{
	gen8_ppgtt_pdpe_t *vaddr;

	pdp->page_directory[pdpe] = pd;
	if (!use_4lvl(vm))
		return;

	vaddr = kmap_atomic_px(pdp);
	vaddr[pdpe] = gen8_pdpe_encode(px_dma(pd), I915_CACHE_LLC);
	kunmap_atomic(vaddr);
}