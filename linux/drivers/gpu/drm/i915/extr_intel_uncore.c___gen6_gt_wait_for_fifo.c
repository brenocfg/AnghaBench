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
typedef  scalar_t__ u32 ;
struct intel_uncore {scalar_t__ fifo_count; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__) ; 
 scalar_t__ GT_FIFO_NUM_RESERVED_ENTRIES ; 
 int /*<<< orphan*/  GT_FIFO_TIMEOUT_MS ; 
 scalar_t__ IS_VALLEYVIEW (int /*<<< orphan*/ ) ; 
 scalar_t__ fifo_free_entries (struct intel_uncore*) ; 
 scalar_t__ wait_for_atomic (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gen6_gt_wait_for_fifo(struct intel_uncore *uncore)
{
	u32 n;

	/* On VLV, FIFO will be shared by both SW and HW.
	 * So, we need to read the FREE_ENTRIES everytime */
	if (IS_VALLEYVIEW(uncore->i915))
		n = fifo_free_entries(uncore);
	else
		n = uncore->fifo_count;

	if (n <= GT_FIFO_NUM_RESERVED_ENTRIES) {
		if (wait_for_atomic((n = fifo_free_entries(uncore)) >
				    GT_FIFO_NUM_RESERVED_ENTRIES,
				    GT_FIFO_TIMEOUT_MS)) {
			DRM_DEBUG("GT_FIFO timeout, entries: %u\n", n);
			return;
		}
	}

	uncore->fifo_count = n - 1;
}