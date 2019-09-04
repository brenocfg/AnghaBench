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
struct TYPE_2__ {int /*<<< orphan*/ * page_directory; } ;
struct i915_hw_ppgtt {TYPE_1__ pdp; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t
i915_page_dir_dma_addr(const struct i915_hw_ppgtt *ppgtt, const unsigned n)
{
	return px_dma(ppgtt->pdp.page_directory[n]);
}