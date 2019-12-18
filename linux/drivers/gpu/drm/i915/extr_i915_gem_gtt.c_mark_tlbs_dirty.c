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
struct i915_ppgtt {int /*<<< orphan*/  pd_dirty_engines; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 

__attribute__((used)) static void mark_tlbs_dirty(struct i915_ppgtt *ppgtt)
{
	ppgtt->pd_dirty_engines = ALL_ENGINES;
}