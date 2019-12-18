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
 int /*<<< orphan*/  REFCOUNT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REFCOUNT_MAX ; 
 int /*<<< orphan*/  overflow_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

void lkdtm_REFCOUNT_INC_NOT_ZERO_OVERFLOW(void)
{
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX);

	pr_info("attempting bad refcount_inc_not_zero() overflow\n");
	if (!refcount_inc_not_zero(&over))
		pr_warn("Weird: refcount_inc_not_zero() reported zero\n");

	overflow_check(&over);
}