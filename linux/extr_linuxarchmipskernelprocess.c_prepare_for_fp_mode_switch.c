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

/* Variables and functions */

__attribute__((used)) static long prepare_for_fp_mode_switch(void *unused)
{
	/*
	 * This is icky, but we use this to simply ensure that all CPUs have
	 * context switched, regardless of whether they were previously running
	 * kernel or user code. This ensures that no CPU currently has its FPU
	 * enabled, or is about to attempt to enable it through any path other
	 * than enable_restore_fp_context() which will wait appropriately for
	 * fp_mode_switching to be zero.
	 */
	return 0;
}