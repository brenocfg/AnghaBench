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
struct i915_address_space {int top; int /*<<< orphan*/ * scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_page_dma (struct i915_address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_scratch_page (struct i915_address_space*) ; 
 int /*<<< orphan*/  px_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_scratch(struct i915_address_space *vm)
{
	int i;

	if (!px_dma(&vm->scratch[0])) /* set to 0 on clones */
		return;

	for (i = 1; i <= vm->top; i++) {
		if (!px_dma(&vm->scratch[i]))
			break;
		cleanup_page_dma(vm, px_base(&vm->scratch[i]));
	}

	cleanup_scratch_page(vm);
}