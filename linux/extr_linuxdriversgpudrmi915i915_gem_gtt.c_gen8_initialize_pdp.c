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
struct i915_page_directory_pointer {int dummy; } ;
struct i915_address_space {int /*<<< orphan*/  scratch_pd; } ;
typedef  int /*<<< orphan*/  gen8_ppgtt_pdpe_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  fill_px (struct i915_address_space*,struct i915_page_directory_pointer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_pdpe_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_initialize_pdp(struct i915_address_space *vm,
				struct i915_page_directory_pointer *pdp)
{
	gen8_ppgtt_pdpe_t scratch_pdpe;

	scratch_pdpe = gen8_pdpe_encode(px_dma(vm->scratch_pd), I915_CACHE_LLC);

	fill_px(vm, pdp, scratch_pdpe);
}