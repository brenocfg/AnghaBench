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
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gt_thread_status (struct intel_uncore*) ; 
 int /*<<< orphan*/  wait_for_atomic_us (int,int) ; 

__attribute__((used)) static void __gen6_gt_wait_for_thread_c0(struct intel_uncore *uncore)
{
	/*
	 * w/a for a sporadic read returning 0 by waiting for the GT
	 * thread to wake up.
	 */
	WARN_ONCE(wait_for_atomic_us(gt_thread_status(uncore) == 0, 5000),
		  "GT thread status wait timed out\n");
}