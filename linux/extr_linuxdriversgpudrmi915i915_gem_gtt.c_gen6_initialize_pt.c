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
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct gen6_hw_ppgtt {int /*<<< orphan*/  scratch_pte; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill32_px (int /*<<< orphan*/ *,struct i915_page_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen6_initialize_pt(struct gen6_hw_ppgtt *ppgtt,
			       struct i915_page_table *pt)
{
	fill32_px(&ppgtt->base.vm, pt, ppgtt->scratch_pte);
}