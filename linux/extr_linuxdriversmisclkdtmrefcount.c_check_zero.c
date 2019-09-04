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
 int /*<<< orphan*/  pr_warn (char*) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_zero(refcount_t *ref)
{
	switch (refcount_read(ref)) {
	case REFCOUNT_SATURATED:
		pr_info("Zero detected: saturated\n");
		break;
	case REFCOUNT_MAX:
		pr_warn("Zero detected: unsafely reset to max\n");
		break;
	case 0:
		pr_warn("Still at zero: refcount_inc/add() must not inc-from-0\n");
		break;
	default:
		pr_err("Fail: refcount went crazy: %d\n", refcount_read(ref));
	}
}