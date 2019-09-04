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
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
#define  REFCOUNT_MAX 129 
#define  REFCOUNT_SATURATED 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_negative(refcount_t *ref, int start)
{
	/*
	 * CONFIG_REFCOUNT_FULL refuses to move a refcount at all on an
	 * over-sub, so we have to track our starting position instead of
	 * looking only at zero-pinning.
	 */
	if (refcount_read(ref) == start) {
		pr_warn("Still at %d: refcount_inc/add() must not inc-from-0\n",
			start);
		return;
	}

	switch (refcount_read(ref)) {
	case REFCOUNT_SATURATED:
		pr_info("Negative detected: saturated\n");
		break;
	case REFCOUNT_MAX:
		pr_warn("Negative detected: unsafely reset to max\n");
		break;
	default:
		pr_err("Fail: refcount went crazy: %d\n", refcount_read(ref));
	}
}