#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t top; int /*<<< orphan*/ * scratch; } ;
struct i915_ppgtt {TYPE_2__ vm; TYPE_1__* pd; } ;
struct i915_page_dma {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct i915_page_dma** entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  px_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t
i915_page_dir_dma_addr(const struct i915_ppgtt *ppgtt, const unsigned int n)
{
	struct i915_page_dma *pt = ppgtt->pd->entry[n];

	return px_dma(pt ?: px_base(&ppgtt->vm.scratch[ppgtt->vm.top]));
}